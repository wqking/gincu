#ifndef GSFMLCAMERADATA_H
#define GSFMLCAMERADATA_H

#include "gincu/gcamera.h"
#include "gsfmlutil.h"

#include <SFML/Graphics.hpp>

namespace gincu {

class GSfmlCameraData : public GCameraData
{
public:
	virtual void apply(const GMatrix44 & matrix, const GRect & viewport, const GRect & /*viewportPixels*/) override
	{
		matrixToSfml(&this->view.getTransform(), matrix);
		matrixToSfml(&this->view.getInverseTransform(), inverseMatrix(matrix));

		this->view.setViewport({
			viewport.x,
			viewport.y,
			viewport.width,
			viewport.height
		});
	}
	
	virtual GPoint mapScreenToWorld(const GPoint & point, const GRect & viewportPixels) const override
	{
		sf::Vector2f normalized;
		normalized.x = -1.f + 2.f * (point.x - viewportPixels.x) / viewportPixels.width;
		normalized.y =  1.f - 2.f * (point.y - viewportPixels.y)  / viewportPixels.height;
		auto pt = this->view.getInverseTransform().transformPoint(normalized);
		return {pt.x, pt.y};
	}

	sf::View view;
};

} //namespace gincu

#endif
