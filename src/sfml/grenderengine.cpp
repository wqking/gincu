#include "../grenderengine.h"
#include "gincu/gtransform.h"
#include "gincu/gimage.h"
#include "gincu/gatlasrender.h"
#include "gincu/gtextrender.h"
#include "gincu/grectrender.h"
#include "gincu/gapplication.h"
#include "gincu/grenderinfo.h"
#include "gincu/gevent.h"
#include "gincu/geventqueue.h"
#include "gincu/gcamera.h"
#include "gsfmlutil.h"
#include "gimagedata.h"
#include "gtextrenderdata.h"
#include "grectrenderdata.h"
#include "grenderenginedata.h"
#include "gcameradata.h"

#include <thread>
#include <mutex>

#include <cassert>

namespace gincu {

namespace {

GRenderEngine * instance = nullptr;

void threadMain(GRenderEngine * renderEngine)
{
	std::shared_ptr<GRenderEngineData> data = renderEngine->getData();

	data->processRenderCommands(); // just to draw background

	while(! data->finished) {
		data->updaterReadyLock.wait();
		data->updaterReadyLock.reset();

		if(! data->renderQueue->empty()) {
			data->processRenderCommands();
			data->window->display();
			data->renderQueue->clear();
		}

		{
			std::lock_guard<std::mutex> lockGuard(data->updaterQueueMutex);
			std::swap(data->renderQueue, data->updaterQueue);
		}
	}
}

template <typename T>
int putImageToVertexArray(T & vertexArray, int index, const sf::Transform & transform, const GRect & rect)
{
	vertexArray[index].position = transform.transformPoint({ 0, 0 });
	vertexArray[index].texCoords = { rect.x, rect.y };
	++index;
	vertexArray[index].position = transform.transformPoint({ rect.width, 0 });
	vertexArray[index].texCoords = { rect.x + rect.width, rect.y };
	++index;
	vertexArray[index].position = transform.transformPoint({ rect.width, rect.height });
	vertexArray[index].texCoords = { rect.x + rect.width, rect.y + rect.height };
	++index;

	vertexArray[index].position = transform.transformPoint({ rect.width, rect.height });
	vertexArray[index].texCoords = { rect.x + rect.width, rect.y + rect.height };
	++index;
	vertexArray[index].position = transform.transformPoint({ 0, rect.height });
	vertexArray[index].texCoords = { rect.x, rect.y + rect.height };
	++index;
	vertexArray[index].position = transform.transformPoint({ 0, 0 });
	vertexArray[index].texCoords = { rect.x, rect.y };
	++index;
	
	return index;
}


} //unnamed namespace

GRenderEngineData::GRenderEngineData()
	:
		window(),
		finished(false),
		updaterQueue(nullptr),
		renderQueue(nullptr)
{
}

void GRenderEngineData::initialize()
{
	this->window->setVerticalSyncEnabled(false);
	this->window->setActive(false);

	this->updaterQueue = &this->queueStorage[0];
	this->renderQueue = &this->queueStorage[1];
}

void GRenderEngineData::processRenderCommands()
{
	this->window->clear(gameColorToSfml(GApplication::getInstance()->getConfigInfo().backgroundColor));

	const int count = (int)this->renderQueue->size();
	for(int i = 0; i < count; ++i) {
		const GRenderCommand & command = this->renderQueue->at(i);
		switch(command.type) {
		case GRenderCommandType::image: {
			int k = i + 1;
			while(k < count) {
				const GRenderCommand & nextCommand = this->renderQueue->at(k);
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
				sf::Sprite sprite(static_cast<GImageData *>(command.renderData.get())->texture, { (int)command.rect.x, (int)command.rect.y, (int)command.rect.width, (int)command.rect.height });
				this->window->draw(sprite, command.sfmlRenderStates);
			}
		}
			break;

		case GRenderCommandType::text: {
			this->window->draw(static_cast<GTextRenderData *>(command.renderData.get())->text, command.sfmlRenderStates);
			break;
		}

		case GRenderCommandType::rect: {
			this->window->draw(static_cast<GRectRenderData *>(command.renderData.get())->rectangle, command.sfmlRenderStates);
			break;
		}

		case GRenderCommandType::vertexTexture: {
			GVertexData * vertexData = static_cast<GVertexData *>(command.renderData.get());
			this->window->draw(&vertexData->vertexList[0], vertexData->count, sf::Triangles, command.sfmlRenderStates);
			break;
		}

		case GRenderCommandType::switchCamera: {
			GCameraData * cameraData = static_cast<GCameraData *>(command.renderData.get());
			this->window->setView(cameraData->view);
			break;
		}

		case GRenderCommandType::none:
			break;
		}
	}
}

void GRenderEngineData::batchDrawImages(const int firstIndex, const int lastIndex)
{
	constexpr int vertexSize = 6;
	const int count = lastIndex - firstIndex + 1;
	
	sf::VertexArray vertexArray(sf::Triangles);
	vertexArray.resize(count * vertexSize);

	int index = 0;
	for(int i = 0; i < count; ++i) {
		const GRenderCommand & command = this->renderQueue->at(i + firstIndex);
		const GRect & rect = command.rect;

		index = putImageToVertexArray(vertexArray, index, command.sfmlRenderStates.transform, rect);
	}

	const GRenderCommand & command = this->renderQueue->at(firstIndex);
	sf::RenderStates renderStates(&static_cast<GImageData *>(command.renderData.get())->texture);
	renderStates.blendMode = command.sfmlRenderStates.blendMode;
	renderStates.shader = command.sfmlRenderStates.shader;
	this->window->draw(vertexArray, renderStates);
}


GRenderEngine * GRenderEngine::getInstance()
{
	return instance;
}

GRenderEngine::GRenderEngine()
	:
		data(std::make_shared<GRenderEngineData>())
{
	assert(instance == nullptr);

	instance = this;
}

GRenderEngine::~GRenderEngine()
{
}

void GRenderEngine::initialize()
{
	const GConfigInfo & configInfo = GApplication::getInstance()->getConfigInfo();

	int flags = 0;
	if(configInfo.fullScreenMode) {
		flags = sf::Style::Fullscreen;
	}
	else {
		flags = sf::Style::Titlebar | sf::Style::Close;
		if(configInfo.resizable) {
			flags |= sf::Style::Resize;
		}
	}

	this->data->window.reset(new sf::RenderWindow(
		sf::VideoMode((int)configInfo.windowSize.width, (int)configInfo.windowSize.height),
		configInfo.caption,
		flags
	));

	this->doInitialize();
}

void GRenderEngine::finalize()
{
}

bool GRenderEngine::peekEvent(GEvent * event)
{
	sf::Event e;

	if(! GRenderEngine::getInstance()->getData()->window->pollEvent(e)) {
		return false;
	}

	switch(e.type) {
	case sf::Event::Closed:
		*event = GEvent(GEventType::windowClosed);
		break;

	case sf::Event::MouseButtonPressed:
	case sf::Event::MouseButtonReleased: {
		GTouchEvent touchEvent = GTouchEvent();
		touchEvent.down = (e.type == sf::Event::MouseButtonPressed);
		touchEvent.screenPosition = {(GCoord)e.mouseButton.x, (GCoord)e.mouseButton.y};
		*event = GEvent((e.type == sf::Event::MouseButtonPressed ? GEventType::touchPressed : GEventType::touchReleased), touchEvent);
	}
		break;

	case sf::Event::MouseMoved: {
		GTouchEvent touchEvent = GTouchEvent();
		touchEvent.down = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		touchEvent.screenPosition = {(GCoord)e.mouseMove.x, (GCoord)e.mouseMove.y};
		*event = GEvent(GEventType::touchMoved, touchEvent);
	}
		break;

	case sf::Event::TouchBegan:
	case sf::Event::TouchEnded: {
		GTouchEvent touchEvent = GTouchEvent();
		touchEvent.finger = e.touch.finger;
		touchEvent.down = (e.type == sf::Event::TouchBegan);
		touchEvent.screenPosition = {(GCoord)e.touch.x, (GCoord)e.touch.y};
		*event = GEvent((e.type == sf::Event::TouchBegan ? GEventType::touchPressed : GEventType::touchReleased), touchEvent);
	}
		break;

	case sf::Event::TouchMoved: {
		GTouchEvent touchEvent = GTouchEvent();
		touchEvent.down = true;
		touchEvent.screenPosition = {(GCoord)e.touch.x, (GCoord)e.touch.y};
		*event = GEvent(GEventType::touchMoved, touchEvent);
	}
		break;

	case sf::Event::Resized:
		*event = GEvent(GEventType::windowResized, GResizeEvent{ (GCoord)e.size.width, (GCoord)e.size.height });
		break;

	case sf::Event::GainedFocus:
		*event = GEvent(GEventType::windowActivated);
		break;

	case sf::Event::LostFocus:
		*event = GEvent(GEventType::windowDeactivated);
		break;

	default:
		break;
	}

	return true;
}

bool GRenderEngine::isAlive() const
{
	return this->data->window->isOpen();
}

void GRenderEngine::draw(const GImage & image, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
{
	this->doDrawTexture(image.getData(), image.getRect(), matrix, renderInfo);
}

void GRenderEngine::draw(const GAtlasRender & atlasRender, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
{
	this->doDrawTexture(atlasRender.getAtlas().getImageData(), atlasRender.getRect(), matrix, renderInfo);
}

void GRenderEngine::doInitialize()
{
	this->data->initialize();

	std::thread thread(&threadMain, this);
	thread.detach();
}

void GRenderEngine::doFinalize()
{
	this->data->finished = true;
	this->data->updaterReadyLock.set();
}

void GRenderEngine::render()
{
	{
		std::lock_guard<std::mutex> lockGuard(this->data->updaterQueueMutex);

		// in case the render thread is too slow to render last frame, let's discard the old frame.
		this->data->updaterQueue->clear();

		GApplication::getInstance()->getEventQueue()->send(GEvent(GEventType::render, this));
	}

	this->data->updaterReadyLock.set();
}

void GRenderEngine::switchCamera(const GCamera & camera)
{
	this->data->updaterQueue->emplace_back(std::make_shared<GCameraData>(*camera.getData()));
}

void GRenderEngine::draw(const GTextRender & text, const GMatrix44 & transform, const GRenderInfo * renderInfo)
{
	this->data->updaterQueue->emplace_back(text.getData(), transform, renderInfo);
}

void GRenderEngine::draw(const GRectRender & rect, const GMatrix44 & transform, const GRenderInfo * renderInfo)
{
	this->data->updaterQueue->emplace_back(rect.getData(), transform, renderInfo);
}

void GRenderEngine::doDrawTexture(const std::shared_ptr<GImageData> & texture, const GRect & rect, const GMatrix44 & transform, const GRenderInfo * renderInfo)
{
	this->data->updaterQueue->emplace_back(texture, rect, transform, renderInfo);
return;
/*
	sf::RenderStates sfmlRenderStates;
	copyBlendAndShaderToSfml(&sfmlRenderStates, renderInfo);
	
	bool needNew = false;
	if(this->data->updaterQueue->empty()) {
		needNew = true;
	}
	else {
		GRenderCommand & command = this->data->updaterQueue->back();
		if(command.type != GRenderCommandType::vertexTexture
			|| static_cast<GVertexData *>(command.renderData.get())->imageData != texture
			|| sfmlRenderStates.blendMode != command.sfmlRenderStates.blendMode
			|| sfmlRenderStates.shader != command.sfmlRenderStates.shader
		) {
			needNew = true;
		}
		else {
			GVertexData * vertexData = static_cast<GVertexData *>(command.renderData.get());
			const int index = (int)vertexData->count;
			if(vertexData->count + 6 >= vertexData->vertexList.size()) {
				vertexData->vertexList.resize(vertexData->count + 64);
			}
			vertexData->count += 6;
			putImageToVertexArray(vertexData->vertexList, index, transform.getMatrix(), rect);
		}
	}
	
	if(needNew) {
		std::shared_ptr<GVertexData> vertexData(new GVertexData{texture});
//		std::shared_ptr<GVertexData> vertexData(allocateObjectOnHeapPool<GVertexData>(sf::VertexArray(sf::Triangles), texture), &freeObjectOnHeapPool<GVertexData>);
		vertexData->count = 6;
		vertexData->vertexList.resize(64);
		putImageToVertexArray(vertexData->vertexList, 0, transform.getMatrix(), rect);
		sfmlRenderStates.texture = &texture->texture;
		this->data->updaterQueue->emplace_back(vertexData, sfmlRenderStates);
	}
*/
}


} //namespace gincu

