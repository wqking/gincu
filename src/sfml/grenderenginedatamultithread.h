#ifndef GRENDERENGINEDATA_H
#define GRENDERENGINEDATA_H

#include "gincu/grenderinfo.h"
#include "gincu/gtransform.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <atomic>
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
	GRenderCommandType type;

	std::shared_ptr<GImageData> imageData;
	std::shared_ptr<GTextRenderData> textData;
	std::shared_ptr<GRectRenderData> rectData;

	GRect rect;
	GTransform transform;
	GRenderInfo renderInfo;
};

class GRenderEngineData
{
private:
	typedef std::vector<GRenderCommand> RenderCommandQueue;

public:
	GRenderEngineData();

	std::unique_ptr<sf::RenderWindow> window;
	sf::View view;

	std::atomic_bool updaterReady;
	std::atomic_bool renderReady;
	std::condition_variable updaterReadySignal;
	std::condition_variable renderReadySignal;
	RenderCommandQueue queueStorage[2];
	RenderCommandQueue * updaterQueue;
	RenderCommandQueue * renderQueue;
};


} //namespace gincu



#endif
