#include "gincu/grenderengine.h"
#include "gincu/gtransform.h"
#include "gincu/gimage.h"
#include "gincu/gspritesheetrender.h"
#include "gincu/gtextrender.h"
#include "gincu/grectrender.h"
#include "gincu/gapplication.h"
#include "gincu/grenderinfo.h"
#include "gincu/glog.h"
#include "gsfmlutil.h"
#include "gimagedata.h"
#include "gtextrenderdata.h"
#include "grectrenderdata.h"
#include "grenderenginedata.h"

#include <thread>
#include <mutex>
#include <chrono>

namespace gincu {


namespace {

void threadMain(GRenderEngine * renderEngine)
{
	std::shared_ptr<GRenderEngineData> data = renderEngine->getData();

	data->processRenderCommands(); // just to draw background

	while(! data->finished) {
		if(! data->renderQueue->empty()) {
			data->processRenderCommands();
		}

		data->window->display();

		{
			std::lock_guard<std::mutex> lockGuard(data->updaterQueueMutex);
			std::swap(data->renderQueue, data->updaterQueue);
			data->updaterQueue->clear();
		}

		data->renderReadyLock.set();
		data->updaterReadyLock.wait();
		data->updaterReadyLock.reset();
	}
}

} //unnamed namespace

GRenderEngineData::GRenderEngineData()
	:
		window(),
		view(),
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
					|| nextCommand.imageData != command.imageData
					|| nextCommand.renderInfo != command.renderInfo) {
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
				const sf::Transform & sfmlTransform = command.transform.getSfmlTransform();
				sf::Sprite sprite(command.imageData->texture, { (int)command.rect.x, (int)command.rect.y, (int)command.rect.width, (int)command.rect.height });
				sf::RenderStates renderStates(sfmlTransform);
				copyBlendAndShaderToSfml(&renderStates, &command.renderInfo);
				this->window->draw(sprite, renderStates);
			}
		}
			break;

		case GRenderCommandType::text: {
			sf::RenderStates renderStates(command.transform.getSfmlTransform());
			copyBlendAndShaderToSfml(&renderStates, &command.renderInfo);
			this->window->draw(command.textData->text, renderStates);
			break;
		}

		case GRenderCommandType::rect: {
			sf::RenderStates renderStates(command.transform.getSfmlTransform());
			copyBlendAndShaderToSfml(&renderStates, &command.renderInfo);
			this->window->draw(command.rectData->rectangle, renderStates);
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
		const sf::Transform & sfmlTransform = command.transform.getSfmlTransform();
		const GRect & rect = command.rect;

		vertexArray[index].position = sfmlTransform.transformPoint({ 0, 0 });
		vertexArray[index].texCoords = { rect.x, rect.y };
		++index;
		vertexArray[index].position = sfmlTransform.transformPoint({ rect.width, 0 });
		vertexArray[index].texCoords = { rect.x + rect.width, rect.y };
		++index;
		vertexArray[index].position = sfmlTransform.transformPoint({ rect.width, rect.height });
		vertexArray[index].texCoords = { rect.x + rect.width, rect.y + rect.height };
		++index;

		vertexArray[index].position = sfmlTransform.transformPoint({ rect.width, rect.height });
		vertexArray[index].texCoords = { rect.x + rect.width, rect.y + rect.height };
		++index;
		vertexArray[index].position = sfmlTransform.transformPoint({ 0, rect.height });
		vertexArray[index].texCoords = { rect.x, rect.y + rect.height };
		++index;
		vertexArray[index].position = sfmlTransform.transformPoint({ 0, 0 });
		vertexArray[index].texCoords = { rect.x, rect.y };
		++index;
	}

	const GRenderCommand & command = this->renderQueue->at(firstIndex);
	sf::RenderStates renderStates(&command.imageData->texture);
	copyBlendAndShaderToSfml(&renderStates, &command.renderInfo);
	this->window->draw(vertexArray, renderStates);
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
		this->renderList();
	}

	this->data->updaterReadyLock.set();
	this->data->renderReadyLock.wait();
	this->data->renderReadyLock.reset();
}

void GRenderEngine::draw(const GTextRender & text, const GTransform & transform, const GRenderInfo * renderInfo)
{
	GRenderCommand command;
	command.type = GRenderCommandType::text;
	command.textData = text.getData();
	command.transform = transform;
	command.renderInfo = *renderInfo;

	this->data->updaterQueue->push_back(command);
}

void GRenderEngine::draw(const GRectRender & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
	GRenderCommand command;
	command.type = GRenderCommandType::rect;
	command.rectData = rect.getData();
	command.transform = transform;
	command.renderInfo = *renderInfo;

	this->data->updaterQueue->push_back(command);
}

void GRenderEngine::doDrawTexture(const std::shared_ptr<GImageData> & texture, const GRect & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
	if(! texture) {
		return;
	}

	GRenderCommand command;
	command.type = GRenderCommandType::image;
	command.imageData = texture;
	command.rect = rect;
	command.transform = transform;
	command.renderInfo = *renderInfo;

	this->data->updaterQueue->push_back(command);
}


} //namespace gincu
