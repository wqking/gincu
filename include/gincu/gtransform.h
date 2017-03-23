#ifndef GTRANSFORM_H
#define GTRANSFORM_H

#include "gincu/ggeometry.h"
#include "gincu/gmatrix.h"

#include "cpgf/gflags.h"

#include <string>

namespace gincu {

class GTransform
{
private:
	enum class Flags {
		flagDirty = 1 << 0,
		flagProjection = 1 << 1
	};

public:
	GTransform();
	explicit GTransform(const GPoint & position, const GScale & scale = {1.0f, 1.0f});
	explicit GTransform(const GMatrix44 & matrix);

	GPoint getPosition() const;
	void setPosition(const GPoint & position);

	GPoint getOrigin() const;
	void setOrigin(const GPoint & origin);

	GScale getScale() const;
	void setScale(const GScale & scale);

	float getRotation() const;
	void setRotation(const float rotation);

	const GMatrix44 & getMatrix() const;
	
	void setProjectionMode(const bool projectionMode);
	
	std::string toDebugString() const;

private:
	void doUpdateTransform() const;
	
	bool isProjectionMode() const { return this->flags.has(Flags::flagProjection); }

private:
	GPoint position;
	GPoint origin;
	GScale scaleValue;
	float rotation; // degree
	mutable cpgf::GFlags<Flags> flags;
	mutable GMatrix44 matrix;
};


} //namespace gincu


#endif
