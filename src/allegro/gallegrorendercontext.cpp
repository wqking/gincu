#include "gallegrorendercontext.h"
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

#include "gallegroutil.h"
#include "gallegrotexturedata.h"
#include "gallegrotextrenderdata.h"
#include "gallegrovertexarraydata.h"
#include "gallegrocameradata.h"

#include "allegro5/allegro_opengl.h"

#include <thread>

namespace gincu {

namespace {


} //unnamed namespace

GAllegroRenderCommand::GAllegroRenderCommand()
{
}

GAllegroRenderCommand::GAllegroRenderCommand(const std::shared_ptr<GCameraData> & cameraData)
	:
		type(GAllegroRenderCommandType::switchCamera),
		renderData(cameraData)
{
}

GAllegroRenderCommand::GAllegroRenderCommand(const std::shared_ptr<GTextureData> & textureData, const GRect & rect, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
	:
		type(GAllegroRenderCommandType::image),
		renderData(textureData),
		rect(rect),
		matrix(matrix)
{
}

GAllegroRenderCommand::GAllegroRenderCommand(const std::shared_ptr<GTextRenderData> & textData, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
	:
		type(GAllegroRenderCommandType::text),
		renderData(textData),
		matrix(matrix)
{
}

GAllegroRenderCommand::GAllegroRenderCommand(const std::shared_ptr<GVertexCommand> & vertexCommand, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
	:
		type(GAllegroRenderCommandType::vertexArray),
		renderData(vertexCommand),
		matrix(matrix)
{
}


GAllegroRenderContext::GAllegroRenderContext()
	:
		window(nullptr),
		backgroundColor(colorWhite),
		currentCameraData(nullptr),
		finished(false),
		updaterQueue(nullptr),
		renderQueue(nullptr)
{
}

GAllegroRenderContext::~GAllegroRenderContext()
{
}

void GAllegroRenderContext::initialize(ALLEGRO_DISPLAY * window)
{
	this->window = window;

	this->updaterQueue = &this->queueStorage[0];
	this->renderQueue = &this->queueStorage[1];

	std::thread thread(&GAllegroRenderContext::threadMain, this);
	thread.detach();
}

void GAllegroRenderContext::finalize()
{
}

void GAllegroRenderContext::threadMain()
{
return;
	this->processRenderCommands(); // just to draw background

	while(! this->finished) {
		this->updaterReadyLock.wait();
		this->updaterReadyLock.reset();

		if(! this->renderQueue->empty()) {
			this->processRenderCommands();
			al_flip_display();
			
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

int putImageToVertexArray(GAllegroVertexArrayData * vertexArray, int index, const GMatrix44 & matrix, const GRect & rect)
{
	GColor color = colorWhite;
	vertexArray->setAt(index++, transformPoint(matrix, { 0, 0 }), color, { rect.x, rect.y });
	vertexArray->setAt(index++, transformPoint(matrix, { rect.width, 0 }), color, { rect.x + rect.width, rect.y });
	vertexArray->setAt(index++, transformPoint(matrix, { rect.width, rect.height }), color, { rect.x + rect.width, rect.y + rect.height });
	vertexArray->setAt(index++, transformPoint(matrix, { rect.width, rect.height }), color, { rect.x + rect.width, rect.y + rect.height });
	vertexArray->setAt(index++, transformPoint(matrix, { 0, rect.height }), color, { rect.x, rect.y + rect.height });
	vertexArray->setAt(index++, transformPoint(matrix, { 0, 0 }), color, { rect.x, rect.y });
	return index;
}

void GAllegroRenderContext::processRenderCommands()
{
	this->currentCameraData = nullptr;

	al_reset_clipping_rectangle();
	al_clear_to_color(gameColorToAllegro(this->backgroundColor));

	const int count = (int)this->renderQueue->size();
	for(int i = 0; i < count; ++i) {
		const GAllegroRenderCommand & command = this->renderQueue->at(i);
		switch(command.type) {
		case GAllegroRenderCommandType::image: {
			int k = i + 1;
			while(k < count) {
				const GAllegroRenderCommand & nextCommand = this->renderQueue->at(k);
				if(nextCommand.type != command.type
					|| nextCommand.renderData != command.renderData
//					|| nextCommand.allegroRenderStates.blendMode != command.allegroRenderStates.blendMode
//					|| nextCommand.allegroRenderStates.shader != command.allegroRenderStates.shader
				) {
					break;
				}
				++k;
			}

			--k;

			if(k > i) {
				this->batchDrawImages(i, k);
				i = k;
			}
			else {

				GAllegroTextureData * textureData = static_cast<GAllegroTextureData *>(command.renderData.get());
				this->allegroApplyMatrix(command.matrix);
				al_draw_bitmap_region(textureData->image, command.rect.x, command.rect.y, command.rect.width, command.rect.height, 0, 0, 0);
			}
		}
			break;

		case GAllegroRenderCommandType::text: {
//			this->window->draw(static_cast<GAllegroTextRenderData *>(command.renderData.get())->text, command.allegroRenderStates);
			break;
		}

		case GAllegroRenderCommandType::vertexArray: {
			const GVertexCommand * vertexCommand = static_cast<GVertexCommand *>(command.renderData.get());
			GAllegroVertexArrayData * data = static_cast<GAllegroVertexArrayData *>(vertexCommand->vertexArrayData.get());
			ALLEGRO_BITMAP * texture = nullptr;
			if(vertexCommand->textureData) {
				texture = static_cast<GAllegroTextureData *>(vertexCommand->textureData.get())->image;
			}
			this->allegroApplyMatrix(command.matrix);
			al_draw_prim(&data->vertexArray[0], nullptr, texture, 0, data->vertexArray.size(), primitiveToAllegro(vertexCommand->primitive));
			break;
		}

		case GAllegroRenderCommandType::switchCamera: {
			this->currentCameraData = static_cast<GAllegroCameraData *>(command.renderData.get());
			allegroApplyProjectionMatrix(this->currentCameraData->matrix);
			break;
		}

		case GAllegroRenderCommandType::none:
			break;
		}
	}

	this->currentCameraData = nullptr;
}

void GAllegroRenderContext::batchDrawImages(const int firstIndex, const int lastIndex)
{
	constexpr int vertexSize = 6;
	const int count = lastIndex - firstIndex + 1;
	
	GAllegroVertexArrayData vertexArray;
	vertexArray.resize(count * vertexSize);

	int index = 0;
	for(int i = 0; i < count; ++i) {
		const GAllegroRenderCommand & command = this->renderQueue->at(i + firstIndex);
		const GRect & rect = command.rect;

		index = putImageToVertexArray(&vertexArray, index, command.matrix, rect);
	}

	const GAllegroRenderCommand & command = this->renderQueue->at(firstIndex);
	GAllegroTextureData * textureData = static_cast<GAllegroTextureData *>(command.renderData.get());
	this->allegroApplyMatrix(identityMatrix);
	al_draw_prim(&vertexArray.vertexArray[0], nullptr, textureData->image, 0, vertexArray.vertexArray.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
}

void GAllegroRenderContext::allegroApplyMatrix(const GMatrix44 & matrix)
{
	al_use_transform((ALLEGRO_TRANSFORM *)&matrix[0][0]);

	if(this->currentCameraData != nullptr) {
		const GRect & rect = this->currentCameraData->viewportPixels;
		glViewport(
			rect.x,
			al_get_display_height(this->window) - (rect.y + rect.height),
			rect.width,
			rect.height
		);
		//al_set_clipping_rectangle(rect.x, rect.y, rect.width, rect.height);
	}
}

void GAllegroRenderContext::setBackgroundColor(const GColor color)
{
	this->backgroundColor = color;
}

void GAllegroRenderContext::render(const cpgf::GCallback<void (GRenderContext *)> & renderCallback)
{

renderCallback(this);
std::swap(this->updaterQueue, this->renderQueue);
this->processRenderCommands();
this->renderQueue->clear();
al_flip_display();
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

void GAllegroRenderContext::switchCamera(const GCamera & camera)
{
	this->updaterQueue->emplace_back(GDeviceContext::getInstance()->createCameraData(camera.getData().get()));
//	this->updaterQueue->emplace_back(createPooledSharedPtr<GCameraData>(*camera.getData()));
}

void GAllegroRenderContext::draw(
		const GTexture & texture,
		const GRect & rect,
		const GMatrix44 & matrix,
		const GRenderInfo * renderInfo
	)
{
	this->updaterQueue->emplace_back(texture.getData(), rect, matrix, renderInfo);
}

void GAllegroRenderContext::draw(
		const GTextRender & text,
		const GMatrix44 & matrix,
		const GRenderInfo * renderInfo
	)
{
	this->updaterQueue->emplace_back(text.getData(), matrix, renderInfo);
}

void GAllegroRenderContext::draw(
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

