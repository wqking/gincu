#ifndef GAMETRANSFORM_H
#define GAMETRANSFORM_H

#include "engine/geometry.h"
#include "engine/renderanchor.h"

#include <SFML/Graphics/Transform.hpp>

namespace gincu {

class GameTransform
{
public:
	GameTransform();
	explicit GameTransform(const GamePoint & position, const float scale = 1.0f);
	explicit GameTransform(const sf::Transform & sfmlTransform);

	GamePoint getPosition() const;
	void setPosition(const GamePoint & position);

	GamePoint getOrigin() const;
	void setOrigin(const GamePoint & origin);

	float getScale() const;
	void setScale(const float scale);

	const sf::Transform & getSfmlTransform() const;
	
	GameTransform multiply(const GameTransform & other) const;

	void translate(const GamePoint & offset);

private:
	void doUpdateTransform() const;

private:
	GamePoint position;
	GamePoint origin;
	GameScale scale;
	float rotation;
	mutable bool needReloadTransform;
	mutable sf::Transform sfmlTransform;
};


} //namespace gincu


#endif
