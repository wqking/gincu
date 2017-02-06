#ifndef GTEXT_H
#define GTEXT_H

#include "gincu/gcolor.h"
#include "gincu/ggeometry.h"
#include "gincu/grenderanchor.h"

#include <string>
#include <memory>

namespace gincu{

class GameTransform;
struct RenderInfo;
class GameTextResource;
class GameImageResource;

class GameText
{
public:
	GameText();
	explicit GameText(const int fontSize);
	~GameText();

	void setText(const std::string & text);
	void setColor(const GameColor textColor);
	void setTextAndColor(const std::string & text, const GameColor textColor);

	void draw(const GameTransform & transform, const RenderInfo * renderInfo);

	GameSize getSize() const;

	const std::shared_ptr<GameTextResource> & getResource() const { return this->resource; }

	const GameImageResource * getTexture() const { return nullptr; }

private:
	std::shared_ptr<GameTextResource> resource;
};


} //namespace gincu

#endif
