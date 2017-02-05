#ifndef GAMETEXT_H
#define GAMETEXT_H

#include "engine/gamecolor.h"
#include "engine/geometry.h"
#include "engine/renderanchor.h"

#include <string>
#include <memory>

namespace gincu{

class GameTransform;
class GameTextResource;

class GameText
{
public:
	GameText();
	explicit GameText(const int fontSize);
	~GameText();

	void setText(const std::string & text);
	void setColor(const GameColor textColor);
	void setTextAndColor(const std::string & text, const GameColor textColor);

	void draw(const GameTransform & transform);

	GameSize getSize() const;

	const std::shared_ptr<GameTextResource> & getResource() const { return this->resource; }

	void * getBatchGroup() const { return nullptr; }

private:
	std::shared_ptr<GameTextResource> resource;
};


} //namespace gincu

#endif
