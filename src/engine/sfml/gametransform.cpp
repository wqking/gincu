#include "engine/gametransform.h"
#include "framework/util.h"

#include <cmath>

namespace gincu {

GameTransform::GameTransform()
	:
		position(),
		origin(),
		scaleValue{1, 1},
		rotation(0),
		needReloadTransform(false)
{
}

GameTransform::GameTransform(const GamePoint & position, const GameScale & scale)
	:
		position(position),
		origin(),
		scaleValue(scale),
		rotation(0),
		needReloadTransform(true)
{
}

GameTransform::GameTransform(const sf::Transform & sfmlTransform)
	:
		position(),
		origin(),
		scaleValue{1, 1},
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
	return this->scaleValue;
}

void GameTransform::setScale(const GameScale & scale)
{
	this->scaleValue = scale;
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
		const float angle = -degreeToRadian(this->rotation);
		const float cosine = (float)(std::cos(angle));
		const float sine = (float)(std::sin(angle));
		const float sxc = this->scaleValue.x * cosine;
		const float syc = this->scaleValue.y * cosine;
		const float sxs = this->scaleValue.x * sine;
		const float sys = this->scaleValue.y * sine;
		const float tx = -this->origin.x * sxc - this->origin.y * sys + this->position.x;
		const float ty =  this->origin.x * sxs - this->origin.y * syc + this->position.y;

        this->sfmlTransform = sf::Transform( sxc, sys, tx,
                                -sxs, syc, ty,
                                 0.f, 0.f, 1.f);
	}
}

GameScale GameTransform::getDecompositedScale() const
{
	this->doUpdateTransform();
	const auto p1 = this->sfmlTransform.transformPoint(0, 0);
	const auto p2 = this->sfmlTransform.transformPoint(1, 1);
	return { p2.x - p1.x, p2.y - p1.y };
/*
	const float angle  = -degreeToRadian(this->rotation);
	const float * matrix = this->sfmlTransform.getMatrix();

	const float cosine = (float)(std::cos(angle));
	if(cosine != 0) {
		const float sxc = matrix[0];
		const float syc = matrix[5];
		return { sxc / cosine, syc / cosine };
	}
	else {
		const float sine = (float)(std::sin(angle));
		const float sxs = -matrix[1];
		const float sys = matrix[4];
		return { sxs / sine, sys / sine };
	}
*/
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

void GameTransform::scale(const GameScale & scale)
{
	this->doUpdateTransform();
	this->sfmlTransform.scale({scale.x, scale.y});
}


} //namespace gincu

