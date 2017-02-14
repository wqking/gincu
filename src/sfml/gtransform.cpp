#include "gincu/gtransform.h"
#include "gincu/gutil.h"

#include <cmath>

namespace gincu {

GTransform::GTransform()
	:
		position(),
		origin(),
		scaleValue{1, 1},
		rotation(0),
		flags()
{
}

GTransform::GTransform(const GPoint & position, const GScale & scale)
	:
		position(position),
		origin(),
		scaleValue(scale),
		rotation(0),
		flags(Flags::flagDirty)
{
}

GTransform::GTransform(const sf::Transform & sfmlTransform)
	:
		position(),
		origin(),
		scaleValue{1, 1},
		rotation(0),
		flags(),
		sfmlTransform(sfmlTransform)
{
}

GPoint GTransform::getPosition() const
{
	return this->position;
}

void GTransform::setPosition(const GPoint & position)
{
	this->position = position;
	this->flags.set(Flags::flagDirty);
}

GPoint GTransform::getOrigin() const
{
	return this->origin;
}

void GTransform::setOrigin(const GPoint & origin)
{
	if(this->origin != origin) {
		this->origin = origin;
		this->flags.set(Flags::flagDirty);
	}
}

GScale GTransform::getScale() const
{
	return this->scaleValue;
}

void GTransform::setScale(const GScale & scale)
{
	this->scaleValue = scale;
	this->flags.set(Flags::flagDirty);
}

float GTransform::getRotation() const
{
	return this->rotation;
}

void GTransform::setRotation(const float rotation)
{
	this->rotation = rotation;
	this->flags.set(Flags::flagDirty);
}

void GTransform::doUpdateTransform() const
{
	if(this->flags.has(Flags::flagDirty)) {
		this->flags.clear(Flags::flagDirty);
		
		if(! this->isProjectionMode()) {
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
		else {
			// below code is from SFML View class
			// "origin" is borrowed as the camera size.
			float angle  = degreeToRadian(this->rotation);
			const float cosine = (float)(std::cos(angle));
			const float sine = (float)(std::sin(angle));
			GPoint pos = -this->position;
			pos.x += this->origin.x / 2;
			pos.y += this->origin.y / 2;
			float tx     = -pos.x * cosine - pos.y * sine + pos.x;
			float ty     =  pos.x * sine - pos.y * cosine + pos.y;

			// Projection components
			float a =  2.f / this->origin.x;
			float b = -2.f / this->origin.y;
			float c = -a * pos.x;
			float d = -b * pos.y;

			// Rebuild the projection matrix
			this->sfmlTransform = sf::Transform( a * cosine, a * sine,   a * tx + c,
									-b * sine,   b * cosine, b * ty + d,
									 0.f,        0.f,        1.f);
		}
	}
}

GScale GTransform::getDecompositedScale() const
{
	this->doUpdateTransform();
	const auto p1 = this->sfmlTransform.transformPoint(0, 0);
	const auto p2 = this->sfmlTransform.transformPoint(1, 0);
	const auto p3 = this->sfmlTransform.transformPoint(0, 1);
	return { p2.x - p1.x, p3.y - p1.y };

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

const sf::Transform & GTransform::getSfmlTransform() const
{
	this->doUpdateTransform();
	return this->sfmlTransform;
}

GTransform GTransform::multiply(const GTransform & other) const
{
	this->doUpdateTransform();
	other.doUpdateTransform();

	return GTransform(this->sfmlTransform * other.sfmlTransform);
}

void GTransform::translate(const GPoint & offset)
{
	this->doUpdateTransform();
	this->sfmlTransform.translate({offset.x, offset.y});
}

void GTransform::scale(const GScale & scale)
{
	this->doUpdateTransform();
	this->sfmlTransform.scale({scale.x, scale.y});
}

void GTransform::setProjectionMode(const bool projectionMode) const
{
	if(projectionMode != this->isProjectionMode()) {
		this->flags.set(Flags::flagDirty);
		this->flags.setByBool(Flags::flagProjection, projectionMode);
	}
}


} //namespace gincu

