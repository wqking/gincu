#ifndef GSDLRENDERCONTEXT_H
#define GSDLRENDERCONTEXT_H

#include "gincu/grendercontext.h"

#include "gsdlutil.h"

#include "SDL_gpu.h"

#include <vector>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace gincu {

enum class GSdlRenderCommandType
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

struct GVertexCommand
{
	std::shared_ptr<GVertexArrayData> vertexArrayData;
	GPrimitive primitive;
	std::shared_ptr<GTextureData> textureData;
};

struct GSdlRenderCommand
{
	GSdlRenderCommand();
	GSdlRenderCommand(const std::shared_ptr<GCameraData> & cameraData);
	GSdlRenderCommand(const std::shared_ptr<GTextureData> & textureData, const GRect & rect, const GMatrix44 & matrix, const GRenderInfo * renderInfo);
	GSdlRenderCommand(const std::shared_ptr<GTextRenderData> & textData, const GMatrix44 & matrix, const GRenderInfo * renderInfo);
	GSdlRenderCommand(const std::shared_ptr<GVertexCommand> & vertexCommand, const GMatrix44 & matrix, const GRenderInfo * renderInfo);

	GSdlRenderCommandType type;

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

class GSdlRenderContext : public GRenderContext
{
private:
	typedef std::vector<GSdlRenderCommand> RenderCommandQueue;

public:
	GSdlRenderContext();
	~GSdlRenderContext();

	void initialize(GPU_Target * window);
	void finalize();

private:
	void threadMain();
	void processRenderCommands();
	void batchDrawImages(const int firstIndex, const int lastIndex);

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
	GPU_Target * window;
	GColor backgroundColor;

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

