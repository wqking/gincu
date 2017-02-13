#ifndef GRENDERENGINEDATA_H
#define GRENDERENGINEDATA_H

#include "gincu/grenderinfo.h"
#include "gincu/gtransform.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace gincu {

enum class GRenderCommandType
{
	none,
	image,
	text,
	rect
};

class GImageData;
class GTextRenderData;
class GRectRenderData;

struct GRenderCommand
{
	GRenderCommand() {}

	GRenderCommand(const std::shared_ptr<GImageData> & imageData, const GRect & rect, const GTransform & transform, const GRenderInfo * renderInfo)
		:
			type(GRenderCommandType::image),
			imageData(imageData),
			rect(rect),
			sfmlRenderStates(transform.getSfmlTransform())
	{
		copyBlendAndShaderToSfml(&this->sfmlRenderStates, renderInfo);
	}

	GRenderCommand(const std::shared_ptr<GTextRenderData> & textData, const GTransform & transform, const GRenderInfo * renderInfo)
		:
			type(GRenderCommandType::text),
			textData(textData),
			sfmlRenderStates(transform.getSfmlTransform())
	{
		copyBlendAndShaderToSfml(&this->sfmlRenderStates, renderInfo);
	}

	GRenderCommand(const std::shared_ptr<GRectRenderData> & rectData, const GTransform & transform, const GRenderInfo * renderInfo)
		:
			type(GRenderCommandType::rect),
			rectData(rectData),
			sfmlRenderStates(transform.getSfmlTransform())
	{
		copyBlendAndShaderToSfml(&this->sfmlRenderStates, renderInfo);
	}

	GRenderCommandType type;

	std::shared_ptr<GImageData> imageData;
	std::shared_ptr<GTextRenderData> textData;
	std::shared_ptr<GRectRenderData> rectData;

	GRect rect;
	sf::RenderStates sfmlRenderStates;
};

class GRenderEngineLock
{
public:
	GRenderEngineLock() : value(false) {}

	void set() {
		this->value = true;
		this->signal.notify_one();
	}

	void reset() {
		this->value = false;
	}

	void wait() {
		std::unique_lock<std::mutex> lock(this->mutex);
		this->signal.wait(lock, [=]() { return (bool)this->value; });
	}

private:
	std::atomic_bool value;
	std::mutex mutex;
	std::condition_variable signal;
};

class GRenderEngineData
{
private:
	typedef std::vector<GRenderCommand> RenderCommandQueue;

public:
	GRenderEngineData();

	void initialize();
	void processRenderCommands();
	void batchDrawImages(const int firstIndex, const int lastIndex);

	std::unique_ptr<sf::RenderWindow> window;
	sf::View view;

	std::atomic_bool finished;
	GRenderEngineLock updaterReadyLock;
	GRenderEngineLock renderReadyLock;
	RenderCommandQueue queueStorage[2];
	RenderCommandQueue * updaterQueue;
	RenderCommandQueue * renderQueue;
	std::mutex updaterQueueMutex;
};


} //namespace gincu



#endif
