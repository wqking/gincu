#ifndef GRENDERENGINEDATA_H
#define GRENDERENGINEDATA_H

#include "gincu/grenderinfo.h"
#include "gincu/gtransform.h"
#include "gtexturedata.h"

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
	rect,
	vertexArray,
	switchCamera
};

class GTextureData;
class GTextRenderData;
class GRectRenderData;
class GCameraData;
class GVertexArrayData;
enum class GPrimitive;

struct GVertexCommand
{
	std::shared_ptr<GVertexArrayData> vertexArrayData;
	GPrimitive primitive;
	std::shared_ptr<GTextureData> textureData;
};

struct GRenderCommand
{
	GRenderCommand() {}

	GRenderCommand(const std::shared_ptr<GCameraData> & cameraData)
		:
			type(GRenderCommandType::switchCamera),
			renderData(cameraData)
	{
	}

	GRenderCommand(const std::shared_ptr<GTextureData> & textureData, const GRect & rect, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
		:
			type(GRenderCommandType::image),
			renderData(textureData),
			rect(rect),
			sfmlRenderStates(matrixToSfml(matrix))
	{
		copyBlendAndShaderToSfml(&this->sfmlRenderStates, renderInfo);
	}

	GRenderCommand(const std::shared_ptr<GTextRenderData> & textData, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
		:
			type(GRenderCommandType::text),
			renderData(textData),
			sfmlRenderStates(matrixToSfml(matrix))
	{
		copyBlendAndShaderToSfml(&this->sfmlRenderStates, renderInfo);
	}

	GRenderCommand(const std::shared_ptr<GRectRenderData> & rectData, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
		:
			type(GRenderCommandType::rect),
			renderData(rectData),
			sfmlRenderStates(matrixToSfml(matrix))
	{
		copyBlendAndShaderToSfml(&this->sfmlRenderStates, renderInfo);
	}

	GRenderCommand(const std::shared_ptr<GVertexCommand> & vertexCommand, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
		:
		type(GRenderCommandType::vertexArray),
		renderData(vertexCommand),
		sfmlRenderStates(matrixToSfml(matrix))
	{
		copyBlendAndShaderToSfml(&this->sfmlRenderStates, renderInfo);
		if(vertexCommand->textureData) {
			this->sfmlRenderStates.texture = &vertexCommand->textureData->texture;
		}
	}

	GRenderCommandType type;

	std::shared_ptr<void> renderData;

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

	std::atomic_bool finished;
	GRenderEngineLock updaterReadyLock;
	RenderCommandQueue queueStorage[2];
	RenderCommandQueue * updaterQueue;
	RenderCommandQueue * renderQueue;
	std::mutex updaterQueueMutex;
};


} //namespace gincu



#endif
