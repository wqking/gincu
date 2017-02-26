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
#include "gincu/gapplication.h"

#include "gallegroutil.h"
#include "gallegrotexturedata.h"
#include "gallegrotextrenderdata.h"
#include "gallegrovertexarraydata.h"
#include "gallegrocameradata.h"

#include "allegro5/allegro_opengl.h"

#include <thread>

namespace gincu {

namespace {

int blendEquationToAllegro(const GBlendEquation & equation)
{
	static const int values[] = {
		ALLEGRO_ADD,
		ALLEGRO_SRC_MINUS_DEST,
		ALLEGRO_DEST_MINUS_SRC,
	};

	const int index = (int)equation;
	if(index >= 0 && index <= sizeof(values) / sizeof(values[0])) {
		return values[index];
	}
	
	return values[0];
}

int blendFuncToAllegro(const GBlendFunc & func)
{
	static const int values[] = {
		ALLEGRO_ZERO,
		ALLEGRO_ONE,
		ALLEGRO_SRC_COLOR,
		ALLEGRO_INVERSE_SRC_COLOR,
		ALLEGRO_DEST_COLOR,
		ALLEGRO_INVERSE_DEST_COLOR,
		ALLEGRO_ALPHA,
		ALLEGRO_INVERSE_ALPHA,
		ALLEGRO_ZERO, // destAlpha is not supported
		ALLEGRO_ZERO, // oneMinusDestAlpha is not supported
	};

	const int index = (int)func;
	if(index >= 0 && index <= sizeof(values) / sizeof(values[0])) {
		return values[index];
	}

	return values[0];
}


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
	this->doCopyRenderInfo(renderInfo);
}

GAllegroRenderCommand::GAllegroRenderCommand(const std::shared_ptr<GTextRenderData> & textData, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
	:
		type(GAllegroRenderCommandType::text),
		renderData(textData),
		matrix(matrix)
{
	this->doCopyRenderInfo(renderInfo);
}

GAllegroRenderCommand::GAllegroRenderCommand(const std::shared_ptr<GVertexCommand> & vertexCommand, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
	:
		type(GAllegroRenderCommandType::vertexArray),
		renderData(vertexCommand),
		matrix(matrix)
{
	this->doCopyRenderInfo(renderInfo);
}

void GAllegroRenderCommand::doCopyRenderInfo(const GRenderInfo * renderInfo)
{
	this->blendMode = renderInfo->blendMode;
}

GAllegroRenderContext::GAllegroRenderContext()
	:
		multiThread(true),
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

void GAllegroRenderContext::initialize(const bool multiThread)
{
	this->multiThread = multiThread;

	this->updaterQueue = &this->queueStorage[0];
	this->renderQueue = &this->queueStorage[1];

	if(this->multiThread) {
		std::thread thread(&GAllegroRenderContext::threadMain, this);
		thread.detach();
	}
	else {
		this->doInitializeWindow();
	}
}

void GAllegroRenderContext::finalize()
{
	if(this->multiThread) {
		this->finished = true;
		this->updaterReadyLock.set();
		this->finishedLock.wait();
	}
	else {
		this->doFinalizeWindow();
	}
}

void GAllegroRenderContext::doInitializeWindow()
{
	if(this->window != nullptr) {
		return;
	}

	const GConfigInfo & configInfo = GApplication::getInstance()->getConfigInfo();

	al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_RESIZABLE | ALLEGRO_WINDOWED);
	this->window = al_create_display(configInfo.windowSize.width, configInfo.windowSize.height);
}

void GAllegroRenderContext::doFinalizeWindow()
{
	if(this->window != nullptr) {
		al_destroy_display(this->window);
	}
}

void GAllegroRenderContext::threadMain()
{
	this->doInitializeWindow();

	this->processRenderCommands(); // just to draw background

	while(! this->finished) {
		this->updaterReadyLock.wait();
		this->updaterReadyLock.reset();

		if(this->finished) {
			break;
		}

		if(! this->renderQueue->empty()) {
			// The bitmaps loaded from the main thread is memory bitmap, which will be rendered using soft-render, which is super slow.
			// al_convert_memory_bitmaps converts all memory bitmap to GPU.
			al_convert_memory_bitmaps();

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

	this->doFinalizeWindow();

	this->finishedLock.set();
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
					|| nextCommand.blendMode != command.blendMode
//					|| nextCommand.allegroRenderStates.shader != command.allegroRenderStates.shader
				) {
					break;
				}
				++k;
			}

			--k;

			// Event there is only one image, we still use our routine to render it.
			// We can't use any Allegro bitmap drawing function such as al_draw_bitmap_region
			// because those functions reset the projection matrix that cause GCamera stops working.
			this->batchDrawImages(i, k);
			i = k;
		}
			break;

		case GAllegroRenderCommandType::text: {
			GAllegroTextRenderData * data = static_cast<GAllegroTextRenderData *>(command.renderData.get());
			this->allegroApplyBlendMode(command.blendMode);
			this->allegroApplyMatrix(command.matrix);
			al_draw_text(static_cast<const GAllegroFontData *>(data->font.getData().get())->font, gameColorToAllegro(data->color), 0, 0, 0, data->text.c_str());
			break;
		}

		case GAllegroRenderCommandType::vertexArray: {
			const GVertexCommand * vertexCommand = static_cast<GVertexCommand *>(command.renderData.get());
			GAllegroVertexArrayData * data = static_cast<GAllegroVertexArrayData *>(vertexCommand->vertexArrayData.get());
			ALLEGRO_BITMAP * texture = nullptr;
			if(vertexCommand->textureData) {
				texture = static_cast<GAllegroTextureData *>(vertexCommand->textureData.get())->image;
			}
			this->allegroApplyBlendMode(command.blendMode);
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
	this->allegroApplyBlendMode(command.blendMode);
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

void GAllegroRenderContext::allegroApplyBlendMode(const GBlendMode & blendMode)
{
	al_set_separate_blender(
		blendEquationToAllegro(blendMode.colorChannel.func),
		blendFuncToAllegro(blendMode.colorChannel.source),
		blendFuncToAllegro(blendMode.colorChannel.dest),
		blendEquationToAllegro(blendMode.alphaChannel.func),
		blendFuncToAllegro(blendMode.alphaChannel.source),
		blendFuncToAllegro(blendMode.alphaChannel.dest)
	);
}

void GAllegroRenderContext::setBackgroundColor(const GColor color)
{
	this->backgroundColor = color;
}

void GAllegroRenderContext::render(const cpgf::GCallback<void (GRenderContext *)> & renderCallback)
{
	if(this->multiThread) {
		{
			std::lock_guard<std::mutex> lockGuard(this->updaterQueueMutex);
		
			this->commandQueueDeleter.clear();

			// in case the render thread is too slow to render last frame, let's discard the old frame.
			this->updaterQueue->clear();

			renderCallback(this);
		}

		this->updaterReadyLock.set();
	}
	else {
		renderCallback(this);
		std::swap(this->updaterQueue, this->renderQueue);
		this->processRenderCommands();
		this->renderQueue->clear();
		al_flip_display();
	}
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

