#ifndef GALLEGRORENDERCONTEXT_H
#define GALLEGRORENDERCONTEXT_H

#include "gincu/grendercontext.h"

#include "gallegroutil.h"

#include "allegro5/allegro.h"

#include <vector>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace gincu {

enum class GAllegroRenderCommandType
{
	none,
	image,
	text,
	vertexArray,
	switchCamera
};

class GTextureData;
class GTextRenderData;
class GCameraData;
class GVertexArrayData;
enum class GPrimitive;
class GAllegroCameraData;

struct GVertexCommand
{
	std::shared_ptr<GVertexArrayData> vertexArrayData;
	GPrimitive primitive;
	std::shared_ptr<GTextureData> textureData;
};

struct GAllegroRenderCommand
{
	GAllegroRenderCommand();
	GAllegroRenderCommand(const std::shared_ptr<GCameraData> & cameraData);
	GAllegroRenderCommand(const std::shared_ptr<GTextureData> & textureData, const GRect & rect, const GMatrix44 & matrix, const GRenderInfo * renderInfo);
	GAllegroRenderCommand(const std::shared_ptr<GTextRenderData> & textData, const GMatrix44 & matrix, const GRenderInfo * renderInfo);
	GAllegroRenderCommand(const std::shared_ptr<GVertexCommand> & vertexCommand, const GMatrix44 & matrix, const GRenderInfo * renderInfo);

	GAllegroRenderCommandType type;

	std::shared_ptr<void> renderData;

	GRect rect;
	
	GMatrix44 matrix;
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

class GAllegroRenderContext : public GRenderContext
{
private:
	typedef std::vector<GAllegroRenderCommand> RenderCommandQueue;

public:
	GAllegroRenderContext();
	~GAllegroRenderContext();

	void initialize(ALLEGRO_DISPLAY * window);
	void finalize();

private:
	void threadMain();
	void processRenderCommands();
	void batchDrawImages(const int firstIndex, const int lastIndex);
	void allegroApplyMatrix(const GMatrix44 & matrix);

private:
	virtual void setBackgroundColor(const GColor color);

	virtual void render(const cpgf::GCallback<void (GRenderContext *)> & renderCallback) override;

	virtual void switchCamera(const GCamera & camera) override;

	virtual void draw(
		const GTexture & texture,
		const GRect & rect,
		const GMatrix44 & matrix,
		const GRenderInfo * renderInfo
	) override;

	virtual void draw(
		const GTextRender & text,
		const GMatrix44 & matrix,
		const GRenderInfo * renderInfo
	) override;

	virtual void draw(
		const GVertexArray & vertexArray,
		const GPrimitive type,
		const GTexture & texture,
		const GMatrix44 & matrix,
		const GRenderInfo * renderInfo
	) override;
	
private:
	ALLEGRO_DISPLAY * window;
	GColor backgroundColor;
	GAllegroCameraData * currentCameraData;

	std::atomic_bool finished;
	GRenderEngineLock updaterReadyLock;
	RenderCommandQueue queueStorage[2];
	RenderCommandQueue * updaterQueue;
	RenderCommandQueue * renderQueue;
	std::mutex updaterQueueMutex;
	std::vector<RenderCommandQueue> commandQueueDeleter;
};


} //namespace gincu


#endif

