#ifndef GTRANSFORM_H
#define GTRANSFORM_H

#include "gincu/ggeometry.h"
#include "gincu/grenderanchor.h"

#include <SFML/Graphics/Transform.hpp>

namespace gincu {

class GTransform
{
public:
	GTransform();
	explicit GTransform(const GPoint & position, const GScale & scale = {1.0f, 1.0f});
	explicit GTransform(const sf::Transform & sfmlTransform);

	GPoint getPosition() const;
	void setPosition(const GPoint & position);

	GPoint getOrigin() const;
	void setOrigin(const GPoint & origin);

	GScale getScale() const;
	void setScale(const GScale & scale);

	float getRotation() const;
	void setRotation(const float rotation);

	const sf::Transform & getSfmlTransform() const;
	
	GTransform multiply(const GTransform & other) const;

	void translate(const GPoint & offset);
	void scale(const GScale & scale);

	GScale getDecompositedScale() const;

private:
	void doUpdateTransform() const;

private:
	GPoint position;
	GPoint origin;
	GScale scaleValue;
	float rotation; // degree
	mutable bool needReloadTransform;
	mutable sf::Transform sfmlTransform;
};


} //namespace gincu


#endif
