#include "gsdlrendercontext.h"
#include "gincu/gdevicecontext.h"
#include "gincu/gtransform.h"
#include "gincu/gimage.h"
#include "gincu/gatlasrender.h"
#include "gincu/gtextrender.h"
#include "gincu/grenderinfo.h"
#include "gincu/gvertexarray.h"
#include "gincu/gprimitive.h"
#include "gincu/gcamera.h"
#include "gincu/gheappool.h"
#include "gincu/glog.h"

#include "gsdlutil.h"
#include "gsdltexturedata.h"
#include "gsdltextrenderdata.h"
#include "gsdlvertexarraydata.h"
#include "gsdlcameradata.h"

#include "SDL_opengl.h"

#include <thread>

namespace gincu {

namespace {


} //unnamed namespace

GSdlRenderCommand::GSdlRenderCommand()
{
}

GSdlRenderCommand::GSdlRenderCommand(const std::shared_ptr<GCameraData> & cameraData)
	:
		type(GSdlRenderCommandType::switchCamera),
		renderData(cameraData)
{
}

GSdlRenderCommand::GSdlRenderCommand(const std::shared_ptr<GTextureData> & textureData, const GRect & rect, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
	:
		type(GSdlRenderCommandType::image),
		renderData(textureData),
		rect(rect),
		matrix(matrix)
{
}

GSdlRenderCommand::GSdlRenderCommand(const std::shared_ptr<GTextRenderData> & textData, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
	:
		type(GSdlRenderCommandType::text),
		renderData(textData),
		matrix(matrix)
{
}

GSdlRenderCommand::GSdlRenderCommand(const std::shared_ptr<GVertexCommand> & vertexCommand, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
	:
		type(GSdlRenderCommandType::vertexArray),
		renderData(vertexCommand),
		matrix(matrix)
{
}


GSdlRenderContext::GSdlRenderContext()
	:
		window(nullptr),
		backgroundColor(colorWhite),
		finished(false),
		updaterQueue(nullptr),
		renderQueue(nullptr)
{
}

GSdlRenderContext::~GSdlRenderContext()
{
}

void GSdlRenderContext::initialize(GPU_Target * window)
{
	this->window = window;

	this->updaterQueue = &this->queueStorage[0];
	this->renderQueue = &this->queueStorage[1];

	std::thread thread(&GSdlRenderContext::threadMain, this);
	thread.detach();
}

void GSdlRenderContext::finalize()
{
}

void GSdlRenderContext::threadMain()
{
	this->processRenderCommands(); // just to draw background

	while(! this->finished) {
		this->updaterReadyLock.wait();
		this->updaterReadyLock.reset();

		if(! this->renderQueue->empty()) {
			this->processRenderCommands();
			GPU_Flip(this->window);
			
			// don't free in render thread
			//this->renderQueue->clear();
		}

		{
			std::lock_guard<std::mutex> lockGuard(this->updaterQueueMutex);
			
			if(! this->renderQueue->empty()) {
				// to be thread safe, we don't free the queue in the render thread.
				// instead we move it to another queue to be freed in the main thread.
				this->commandQueueDeleter.emplace_back();
				std::swap(this->commandQueueDeleter.back(), *(this->renderQueue));
			}
			
			std::swap(this->renderQueue, this->updaterQueue);
		}
	}
}

int putImageToVertexArray(float * vertexArray, int index, const GMatrix44 & matrix, const GRect & rect, const GSize & size)
{
	GPoint point;
	
	const float textureLeft = rect.x / size.width;
	const float textureTop = rect.y / size.height;
	const float textureRight = (rect.x + rect.width) / size.width;
	const float textureBottom = (rect.y + rect.height) / size.height;
	
	point = transformPoint(matrix, { 0, 0 });
	vertexArray[index++] = point.x;
	vertexArray[index++] = point.y;
	vertexArray[index++] = textureLeft;
	vertexArray[index++] = textureTop;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;

	point = transformPoint(matrix, { rect.width, 0 });
	vertexArray[index++] = point.x;
	vertexArray[index++] = point.y;
	vertexArray[index++] = textureRight;
	vertexArray[index++] = textureTop;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;

	point = transformPoint(matrix, { rect.width, rect.height });
	vertexArray[index++] = point.x;
	vertexArray[index++] = point.y;
	vertexArray[index++] = textureRight;
	vertexArray[index++] = textureBottom;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;

	point = transformPoint(matrix, { rect.width, rect.height });
	vertexArray[index++] = point.x;
	vertexArray[index++] = point.y;
	vertexArray[index++] = textureRight;
	vertexArray[index++] = textureBottom;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;

	point = transformPoint(matrix, { 0, rect.height });
	vertexArray[index++] = point.x;
	vertexArray[index++] = point.y;
	vertexArray[index++] = textureLeft;
	vertexArray[index++] = textureBottom;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;

	point = transformPoint(matrix, { 0, 0 });
	vertexArray[index++] = point.x;
	vertexArray[index++] = point.y;
	vertexArray[index++] = textureLeft;
	vertexArray[index++] = textureTop;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;
	vertexArray[index++] = 1.0f;
	
	return index;
}

void GSdlRenderContext::processRenderCommands()
{
//	this->window->clear(gameColorToSdl(this->backgroundColor));
	GPU_Clear(this->window);

	const int count = (int)this->renderQueue->size();
	for(int i = 0; i < count; ++i) {
		const GSdlRenderCommand & command = this->renderQueue->at(i);
		switch(command.type) {
		case GSdlRenderCommandType::image: {
			int k = i + 1;
			while(k < count) {
				const GSdlRenderCommand & nextCommand = this->renderQueue->at(k);
				if(nextCommand.type != command.type
					|| nextCommand.renderData != command.renderData
//					|| nextCommand.sdlRenderStates.blendMode != command.sdlRenderStates.blendMode
//					|| nextCommand.sdlRenderStates.shader != command.sdlRenderStates.shader
				) {
					break;
				}
				++k;
			}

			--k;
k = i;
			if(k > i) {
				this->batchDrawImages(i, k);
				i = k;
			}
			else {
/*
				GPU_PushMatrix();
				GPU_LoadIdentity();
				GPU_MatrixCopy(GPU_GetCurrentMatrix(), &command.matrix[0][0]);
				GPU_Rect src = { (int)command.rect.x, (int)command.rect.y, (int)command.rect.width, (int)command.rect.height };
				GPU_Blit(static_cast<GSdlTextureData *>(command.renderData.get())->image, &src, this->window, 0, 0);
*/

				GSdlTextureData * textureData = static_cast<GSdlTextureData *>(command.renderData.get());
//printf("%s %d %d\n", textureData->fileName.c_str(), (int)textureData->getSize().width, (int)textureData->getSize().height);
				float buffer[6 * 8];
				putImageToVertexArray(buffer, 0, command.matrix, command.rect, textureData->getSize());
				GPU_TriangleBatch(textureData->image, this->window, 6, buffer, 0, nullptr, GPU_BATCH_XY_ST_RGBA);

//				GPU_PopMatrix();
			}
		}
			break;

		case GSdlRenderCommandType::text: {
//			this->window->draw(static_cast<GSdlTextRenderData *>(command.renderData.get())->text, command.sdlRenderStates);
			break;
		}

		case GSdlRenderCommandType::vertexArray: {
			const GVertexCommand * vertexCommand = static_cast<GVertexCommand *>(command.renderData.get());
			GSdlVertexArrayData * data = static_cast<GSdlVertexArrayData *>(vertexCommand->vertexArrayData.get());
/*
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
//			glLoadMatrixf(&data->vertexArray[0]);
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);
            glVertexPointer(2, GL_FLOAT, 8 * 4, &data->vertexArray[0]);
            glColorPointer(4, GL_FLOAT, 8 * 4, &data->vertexArray[0] + 4);
            glDrawArrays(GL_TRIANGLES, 0, data->getCount());
			glPopMatrix();
			break;
*/
			GPU_PushMatrix();
			GPU_LoadIdentity();
//printf("%s\n\n", GPU_GetMatrixString(GPU_GetCurrentMatrix()));
			GPU_MatrixCopy(GPU_GetCurrentMatrix(), &command.matrix[0][0]);
			float * a = GPU_GetCurrentMatrix();
			a[12]= 0; a[13] = 0; a[14] = 0; a[15] = 1;
//printf("%s\n\n", GPU_GetMatrixString(GPU_GetCurrentMatrix()));
			GPU_TriangleBatch(nullptr, this->window, data->getCount(), &data->vertexArray[0], 0, nullptr, GPU_BATCH_XY_ST_RGBA);
			GPU_PopMatrix();
			break;
		}

		case GSdlRenderCommandType::switchCamera: {
			GSdlCameraData * cameraData = static_cast<GSdlCameraData *>(command.renderData.get());
//			this->window->setView(cameraData->view);
			break;
		}

		case GSdlRenderCommandType::none:
			break;
		}
	}
}

void GSdlRenderContext::batchDrawImages(const int firstIndex, const int lastIndex)
{
	constexpr int vertexSize = 6;
	const int count = lastIndex - firstIndex + 1;
	
//	sf::VertexArray vertexArray(sf::Triangles);
//	vertexArray.resize(count * vertexSize);

	int index = 0;
	for(int i = 0; i < count; ++i) {
		const GSdlRenderCommand & command = this->renderQueue->at(i + firstIndex);
		const GRect & rect = command.rect;

//		index = putImageToVertexArray(vertexArray, index, command.sdlRenderStates.transform, rect);
	}

	const GSdlRenderCommand & command = this->renderQueue->at(firstIndex);
//	sf::RenderStates renderStates(&static_cast<GSdlTextureData *>(command.renderData.get())->texture);
//	renderStates.blendMode = command.sdlRenderStates.blendMode;
//	renderStates.shader = command.sdlRenderStates.shader;
//	this->window->draw(vertexArray, renderStates);
}

void GSdlRenderContext::setBackgroundColor(const GColor color)
{
	this->backgroundColor = color;
}

void GSdlRenderContext::render(const cpgf::GCallback<void (GRenderContext *)> & renderCallback)
{

renderCallback(this);
std::swap(this->updaterQueue, this->renderQueue);
this->processRenderCommands();
this->renderQueue->clear();
GPU_Flip(this->window);
return;


	{
		std::lock_guard<std::mutex> lockGuard(this->updaterQueueMutex);
		
		this->commandQueueDeleter.clear();

		// in case the render thread is too slow to render last frame, let's discard the old frame.
		this->updaterQueue->clear();

		renderCallback(this);
	}

	this->updaterReadyLock.set();
}

void GSdlRenderContext::switchCamera(const GCamera & camera)
{
	this->updaterQueue->emplace_back(GDeviceContext::getInstance()->createCameraData(camera.getData().get()));
//	this->updaterQueue->emplace_back(createPooledSharedPtr<GCameraData>(*camera.getData()));
}

void GSdlRenderContext::draw(
		const GTexture & texture,
		const GRect & rect,
		const GMatrix44 & matrix,
		const GRenderInfo * renderInfo
	)
{
	this->updaterQueue->emplace_back(texture.getData(), rect, matrix, renderInfo);
}

void GSdlRenderContext::draw(
		const GTextRender & text,
		const GMatrix44 & matrix,
		const GRenderInfo * renderInfo
	)
{
	this->updaterQueue->emplace_back(text.getData(), matrix, renderInfo);
}

void GSdlRenderContext::draw(
		const GVertexArray & vertexArray,
		const GPrimitive type,
		const GTexture & texture,
		const GMatrix44 & matrix,
		const GRenderInfo * renderInfo
	)
{
	this->updaterQueue->emplace_back(
		std::make_shared<GVertexCommand>(GVertexCommand { vertexArray.getData(), type, texture.getData() }),
		matrix,
		renderInfo
	);
}


} //namespace gincu

