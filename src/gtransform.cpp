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

GTransform::GTransform(const GMatrix44 & matrix)
	:
		position(),
		origin(),
		scaleValue{1, 1},
		rotation(0),
		flags(),
		matrix(matrix)
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

			this->matrix = GMatrix44(
				{ sxc, -sxs, 0, 0},
				{ sys, syc, 0, 0 },
				{ 0, 0, 1, 0 },
				{ tx, ty, 0, 1 }
			);
		}
		else {
			// below code is from SFML View class
			// "origin" is borrowed as the camera size.
			const float angle  = degreeToRadian(this->rotation);
			const float cosine = (float)(std::cos(angle));
			const float sine = (float)(std::sin(angle));
			GPoint pos = this->position;
			pos.x += this->origin.x / 2;
			pos.y += this->origin.y / 2;
			float tx     = -pos.x * cosine - pos.y * sine + pos.x;
			float ty     =  pos.x * sine - pos.y * cosine + pos.y;

			// Projection components
			float a =  2.f / (this->origin.x * this->scaleValue.x);
			float b = -2.f / (this->origin.y * this->scaleValue.y);
			float c = -a * pos.x;
			float d = -b * pos.y;

			// Rebuild the projection matrix
			this->matrix = GMatrix44(
				{ a * cosine, -b * sine, 0, 0 },
				{ a * sine, b * cosine, 0, 0 },
				{ 0, 0, 1, 0 },
				{ a * tx + c, b * ty + d, 0, 1}
			);
		}
	}
}


const GMatrix44 & GTransform::getMatrix() const
{
	this->doUpdateTransform();
	return this->matrix;
}

void GTransform::setProjectionMode(const bool projectionMode)
{
	if(projectionMode != this->isProjectionMode()) {
		this->flags.set(Flags::flagDirty);
		this->flags.setByBool(Flags::flagProjection, projectionMode);
	}
}

std::string GTransform::toDebugString() const
{
	this->doUpdateTransform();

	char buffer[1024];

	sprintf(
		buffer,
		"Position(%d, %d), Origin(%d, %d), Scale(%.2f, %.2f), Rotation(%.2f) \n"
		"%.2f %.2f %.2f %.2f\n"
		"%.2f %.2f %.2f %.2f\n"
		"%.2f %.2f %.2f %.2f\n"
		"%.2f %.2f %.2f %.2f\n"
		,
		(int)this->position.x, (int)this->position.y,
		(int)this->origin.x, (int)this->origin.y,
		(float)this->scaleValue.x, (float)this->scaleValue.y,
		(float)this->rotation,
		this->matrix[0].x, this->matrix[1].x, this->matrix[2].x, this->matrix[3].x,
		this->matrix[0].y, this->matrix[1].y, this->matrix[2].y, this->matrix[3].y,
		this->matrix[0].z, this->matrix[1].z, this->matrix[2].z, this->matrix[3].z,
		this->matrix[0].w, this->matrix[1].w, this->matrix[2].w, this->matrix[3].w
	);

	return buffer;
}


} //namespace gincu

