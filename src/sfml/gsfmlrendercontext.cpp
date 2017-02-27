#include "gsfmlrendercontext.h"
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

#include "gsfmlutil.h"
#include "gsfmltexturedata.h"
#include "gsfmltextrenderdata.h"
#include "gsfmlvertexarraydata.h"
#include "gsfmlcameradata.h"

#include <thread>

namespace gincu {

namespace {

template <typename T>
int putImageToVertexArray(T & vertexArray, int index, const sf::Transform & transform, const GRect & rect, const GColor color)
{
	const auto sfmlColor = gameColorToSfml(color);
	vertexArray[index].position = transform.transformPoint({ 0, 0 });
	vertexArray[index].texCoords = { rect.x, rect.y };
	vertexArray[index].color = sfmlColor;
	++index;
	vertexArray[index].position = transform.transformPoint({ rect.width, 0 });
	vertexArray[index].texCoords = { rect.x + rect.width, rect.y };
	vertexArray[index].color = sfmlColor;
	++index;
	vertexArray[index].position = transform.transformPoint({ rect.width, rect.height });
	vertexArray[index].texCoords = { rect.x + rect.width, rect.y + rect.height };
	vertexArray[index].color = sfmlColor;
	++index;

	vertexArray[index].position = transform.transformPoint({ rect.width, rect.height });
	vertexArray[index].texCoords = { rect.x + rect.width, rect.y + rect.height };
	vertexArray[index].color = sfmlColor;
	++index;
	vertexArray[index].position = transform.transformPoint({ 0, rect.height });
	vertexArray[index].texCoords = { rect.x, rect.y + rect.height };
	vertexArray[index].color = sfmlColor;
	++index;
	vertexArray[index].position = transform.transformPoint({ 0, 0 });
	vertexArray[index].texCoords = { rect.x, rect.y };
	vertexArray[index].color = sfmlColor;
	++index;
	
	return index;
}


} //unnamed namespace

GSfmlRenderCommand::GSfmlRenderCommand()
{
}

GSfmlRenderCommand::GSfmlRenderCommand(const std::shared_ptr<GCameraData> & cameraData)
	:
		type(GSfmlRenderCommandType::switchCamera),
		renderData(cameraData)
{
}

GSfmlRenderCommand::GSfmlRenderCommand(const std::shared_ptr<GTextureData> & textureData, const GRect & rect, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
	:
		type(GSfmlRenderCommandType::image),
		renderData(textureData),
		rect(rect),
		sfmlRenderStates(matrixToSfml(matrix))
{
	this->doCopyRenderInfo(renderInfo);
}

GSfmlRenderCommand::GSfmlRenderCommand(const std::shared_ptr<GTextRenderData> & textData, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
	:
		type(GSfmlRenderCommandType::text),
		renderData(textData),
		sfmlRenderStates(matrixToSfml(matrix))
{
	this->doCopyRenderInfo(renderInfo);
}

GSfmlRenderCommand::GSfmlRenderCommand(const std::shared_ptr<GVertexCommand> & vertexCommand, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
	:
	type(GSfmlRenderCommandType::vertexArray),
	renderData(vertexCommand),
	sfmlRenderStates(matrixToSfml(matrix))
{
	this->doCopyRenderInfo(renderInfo);

	if(vertexCommand->textureData) {
		this->sfmlRenderStates.texture = &static_cast<GSfmlTextureData *>(vertexCommand->textureData.get())->texture;
	}
}

void GSfmlRenderCommand::doCopyRenderInfo(const GRenderInfo * renderInfo)
{
	copyBlendAndShaderToSfml(&this->sfmlRenderStates, renderInfo);
	this->color = renderInfo->color;
}

GSfmlRenderContext::GSfmlRenderContext()
	:
		backgroundColor(colorWhite),
		window(nullptr),
		finished(false),
		updaterQueue(nullptr),
		renderQueue(nullptr)
{
}

GSfmlRenderContext::~GSfmlRenderContext()
{
}

void GSfmlRenderContext::initialize(sf::RenderWindow * window)
{
	this->window = window;

	this->window->setActive(false);

	this->updaterQueue = &this->queueStorage[0];
	this->renderQueue = &this->queueStorage[1];

	std::thread thread(&GSfmlRenderContext::threadMain, this);
	thread.detach();
}

void GSfmlRenderContext::finalize()
{
}

void GSfmlRenderContext::threadMain()
{
	this->processRenderCommands(); // just to draw background

	while(! this->finished) {
		this->updaterReadyLock.wait();
		this->updaterReadyLock.reset();

		if(! this->renderQueue->empty()) {
			this->processRenderCommands();
			this->window->display();
			
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

void GSfmlRenderContext::processRenderCommands()
{
	this->window->clear(gameColorToSfml(this->backgroundColor));

	const int count = (int)this->renderQueue->size();
	for(int i = 0; i < count; ++i) {
		const GSfmlRenderCommand & command = this->renderQueue->at(i);
		switch(command.type) {
		case GSfmlRenderCommandType::image: {
			int k = i + 1;
			while(k < count) {
				const GSfmlRenderCommand & nextCommand = this->renderQueue->at(k);
				if(nextCommand.type != command.type
					|| nextCommand.renderData != command.renderData
					|| nextCommand.sfmlRenderStates.blendMode != command.sfmlRenderStates.blendMode
					|| nextCommand.sfmlRenderStates.shader != command.sfmlRenderStates.shader
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
				sf::Sprite sprite(static_cast<GSfmlTextureData *>(command.renderData.get())->texture, { (int)command.rect.x, (int)command.rect.y, (int)command.rect.width, (int)command.rect.height });
				sprite.setColor(gameColorToSfml(command.color));
				this->window->draw(sprite, command.sfmlRenderStates);
			}
		}
			break;

		case GSfmlRenderCommandType::text: {
			GSfmlTextRenderData * data = static_cast<GSfmlTextRenderData *>(command.renderData.get());
			auto color = gameColorToSfml(command.color);
			data->text.setOutlineColor(color);
			data->text.setFillColor(color);
			this->window->draw(data->text, command.sfmlRenderStates);
			break;
		}

		case GSfmlRenderCommandType::vertexArray: {
			const GVertexCommand * vertexCommand = static_cast<GVertexCommand *>(command.renderData.get());
			GSfmlVertexArrayData * data = static_cast<GSfmlVertexArrayData *>(vertexCommand->vertexArrayData.get());
			this->window->draw(
				&data->vertexArray[0],
				data->vertexArray.size(),
				gamePrimitiveToSfml(vertexCommand->primitive),
				command.sfmlRenderStates
		);
			break;
		}

		case GSfmlRenderCommandType::switchCamera: {
			GSfmlCameraData * cameraData = static_cast<GSfmlCameraData *>(command.renderData.get());
			this->window->setView(cameraData->view);
			break;
		}

		case GSfmlRenderCommandType::none:
			break;
		}
	}
}

void GSfmlRenderContext::batchDrawImages(const int firstIndex, const int lastIndex)
{
	constexpr int vertexSize = 6;
	const int count = lastIndex - firstIndex + 1;
	
	sf::VertexArray vertexArray(sf::Triangles);
	vertexArray.resize(count * vertexSize);

	int index = 0;
	for(int i = 0; i < count; ++i) {
		const GSfmlRenderCommand & command = this->renderQueue->at(i + firstIndex);
		index = putImageToVertexArray(vertexArray, index, command.sfmlRenderStates.transform, command.rect, command.color);
	}

	const GSfmlRenderCommand & command = this->renderQueue->at(firstIndex);
	sf::RenderStates renderStates(&static_cast<GSfmlTextureData *>(command.renderData.get())->texture);
	renderStates.blendMode = command.sfmlRenderStates.blendMode;
	renderStates.shader = command.sfmlRenderStates.shader;
	this->window->draw(vertexArray, renderStates);
}

void GSfmlRenderContext::setBackgroundColor(const GColor color)
{
	this->backgroundColor = color;
}

void GSfmlRenderContext::render(const cpgf::GCallback<void (GRenderContext *)> & renderCallback)
{
	{
		std::lock_guard<std::mutex> lockGuard(this->updaterQueueMutex);
		
		this->commandQueueDeleter.clear();

		// in case the render thread is too slow to render last frame, let's discard the old frame.
		this->updaterQueue->clear();

		renderCallback(this);
	}

	this->updaterReadyLock.set();
}

void GSfmlRenderContext::switchCamera(const GCamera & camera)
{
	this->updaterQueue->emplace_back(GDeviceContext::getInstance()->createCameraData(camera.getData().get()));
//	this->updaterQueue->emplace_back(createPooledSharedPtr<GCameraData>(*camera.getData()));
}

void GSfmlRenderContext::draw(
		const GTexture & texture,
		const GRect & rect,
		const GMatrix44 & matrix,
		const GRenderInfo * renderInfo
	)
{
	this->updaterQueue->emplace_back(texture.getData(), rect, matrix, renderInfo);
}

void GSfmlRenderContext::draw(
		const GTextRender & text,
		const GMatrix44 & matrix,
		const GRenderInfo * renderInfo
	)
{
	this->updaterQueue->emplace_back(text.getData(), matrix, renderInfo);
}

void GSfmlRenderContext::draw(
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

