#include "gincu/gcamera.h"
#include "gincu/gapplication.h"
#include "gincu/grendercontext.h"
#include "gincu/gtransform.h"
#include "gincu/gutil.h"
#include "gcameradata.h"
#include "gsfmlutil.h"
#include "grenderenginedata.h"

namespace gincu {

GCamera::GCamera()
	:
		mask(1),
		viewport{ 0.0f, 0.0f, 1.0f, 1.0f },
		worldSize(GApplication::getInstance()->getConfigInfo().targetViewSize),
		fitStrategy(GCameraFitStrategy::none),
		targetViewSize(GApplication::getInstance()->getConfigInfo().targetViewSize),
		cachedScreenSize{ -1, -1 },
		data(std::make_shared<GCameraData>())
{
}

void GCamera::setViewport(const GRect & viewport)
{
	this->viewport = viewport;
	this->doRequireRefresh();
}

const GRect & GCamera::getViewport() const
{
	this->doRefresh();
	return this->viewport;
}

void GCamera::setTargetViewSize(const GSize & size)
{
	this->targetViewSize = size;
	this->doRequireRefresh();
}

GRect GCamera::getViewportPixels() const
{
	this->doRefresh();

	const GSize screenSize = GApplication::getInstance()->getScreenSize();
	return {
		std::round(screenSize.width * this->viewport.x),
		std::round(screenSize.height * this->viewport.y),
		std::round(screenSize.width * this->viewport.width),
		std::round(screenSize.height * this->viewport.height)
	};
}

void GCamera::setFitStrategy(const GCameraFitStrategy strategy)
{
	this->fitStrategy = strategy;
	this->doRequireRefresh();
}

void GCamera::apply(const GMatrix44 & matrix)
{
	this->doRefresh();

	matrixToSfml(&this->data->view.getTransform(), matrix);
	matrixToSfml(&this->data->view.getInverseTransform(), inverseMatrix(matrix));

	this->data->view.setViewport({
		this->viewport.x,
		this->viewport.y,
		this->viewport.width,
		this->viewport.height
	});
}

GPoint GCamera::mapScreenToCamera(const GPoint & point) const
{
	const GRect viewportPixels = this->getViewportPixels();
	sf::Vector2f normalized;
	normalized.x = -1.f + 2.f * (point.x - viewportPixels.x) / viewportPixels.width;
	normalized.y =  1.f - 2.f * (point.y - viewportPixels.y)  / viewportPixels.height;
	auto pt = this->data->view.getInverseTransform().transformPoint(normalized);
	return {pt.x, pt.y};
}

void GCamera::doRequireRefresh()
{
	this->cachedScreenSize.width = -1;
}

void GCamera::doRefresh() const
{
	if(this->cachedScreenSize != GApplication::getInstance()->getScreenSize()) {
		this->cachedScreenSize = GApplication::getInstance()->getScreenSize();

		switch(this->fitStrategy) {
		case GCameraFitStrategy::none:
			break;
			
		case GCameraFitStrategy::scaleFitFullScreen: {
			const float cachedRatio = this->cachedScreenSize.width / this->cachedScreenSize.height;
			const float targetRatio = this->targetViewSize.width / this->targetViewSize.height;
			if(cachedRatio >= targetRatio) {
				this->viewport.width = targetRatio / cachedRatio;
				this->viewport.height = 1;
			}
			else {
				this->viewport.width = 1;
				this->viewport.height = cachedRatio / targetRatio;
			}
			this->viewport.x = (1.0f - this->viewport.width) / 2.0f;
			this->viewport.y = (1.0f - this->viewport.height) / 2.0f;
		}
			break;
			
		case GCameraFitStrategy::fixed:
			this->viewport.width = this->targetViewSize.width / this->cachedScreenSize.width;
			this->viewport.height = this->targetViewSize.height / this->cachedScreenSize.height;
			break;
		}
	}
}


} //namespace gincu

