#include "engine/gametransform.h"

#include <cmath>

namespace gincu {

GameTransform::GameTransform()
	:
		position(),
		origin(),
		scale{1, 1},
		rotation(0),
		needReloadTransform(false)
{
}

GameTransform::GameTransform(const GamePoint & position, const GameScale & scale)
	:
		position(position),
		origin(),
		scale(scale),
		rotation(0),
		needReloadTransform(true)
{
}

GameTransform::GameTransform(const sf::Transform & sfmlTransform)
	:
		position(),
		origin(),
		scale{1, 1},
		rotation(0),
		needReloadTransform(false),
		sfmlTransform(sfmlTransform)
{
}

GamePoint GameTransform::getPosition() const
{
	return this->position;
}

void GameTransform::setPosition(const GamePoint & position)
{
	this->position = position;
	this->needReloadTransform = true;
}

GamePoint GameTransform::getOrigin() const
{
	return this->origin;
}

void GameTransform::setOrigin(const GamePoint & origin)
{
	if(this->origin != origin) {
		this->origin = origin;
		this->needReloadTransform = true;
	}
}

GameScale GameTransform::getScale() const
{
	return this->scale;
}

void GameTransform::setScale(const GameScale & scale)
{
	this->scale = scale;
	this->needReloadTransform = true;
}

float GameTransform::getRotation() const
{
	return this->rotation;
}

void GameTransform::setRotation(const float rotation)
{
	this->rotation = rotation;
	this->needReloadTransform = true;
}

void GameTransform::doUpdateTransform() const
{
	if(this->needReloadTransform) {
		this->needReloadTransform = false;
		
		// below code is borrowed from SFML.
		float angle  = -this->rotation * 3.141592654f / 180.f;
		float cosine = (float)(std::cos(angle));
		float sine   = (float)(std::sin(angle));
		float sxc    = this->scale.x * cosine;
		float syc    = this->scale.y * cosine;
		float sxs    = this->scale.x * sine;
		float sys    = this->scale.y * sine;
		float tx     = -this->origin.x * sxc - this->origin.y * sys + this->position.x;
		float ty     =  this->origin.x * sxs - this->origin.y * syc + this->position.y;

        this->sfmlTransform = sf::Transform( sxc, sys, tx,
                                -sxs, syc, ty,
                                 0.f, 0.f, 1.f);
	}
}

const sf::Transform & GameTransform::getSfmlTransform() const
{
	this->doUpdateTransform();
	return this->sfmlTransform;
}

GameTransform GameTransform::multiply(const GameTransform & other) const
{
	this->doUpdateTransform();
	other.doUpdateTransform();

	return GameTransform(this->sfmlTransform * other.sfmlTransform);
}

void GameTransform::translate(const GamePoint & offset)
{
	this->doUpdateTransform();
	this->sfmlTransform.translate({offset.x, offset.y});
}


} //namespace gincu

