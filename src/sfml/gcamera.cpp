#include "gincu/gcamera.h"
#include "gincu/gapplication.h"
#include "gincu/grenderengine.h"
#include "gincu/gtransform.h"
#include "gincu/gaccesshack.h"
#include "gcameradata.h"
#include "gsfmlutil.h"
#include "grenderenginedata.h"

GINCU_ENABLE_ACCESS_HACK(sfmlView_m_transform, ::sf::View, m_transform, sf::Transform);
GINCU_ENABLE_ACCESS_HACK(sfmlView_m_inverseTransform, ::sf::View, m_inverseTransform, sf::Transform);
GINCU_ENABLE_ACCESS_HACK(sfmlView_m_transformUpdated, ::sf::View, m_transformUpdated, bool);
GINCU_ENABLE_ACCESS_HACK(sfmlView_m_invTransformUpdated, ::sf::View, m_invTransformUpdated, bool);

namespace gincu {

GCamera::GCamera()
	:
		mask(1),
		viewport(createRect(GPoint(), GApplication::getInstance()->getWindowSize())),
		size(GApplication::getInstance()->getWindowSize()),
		data(std::make_shared<GCameraData>())
{
}

void GCamera::apply(const GMatrix44 & matrix)
{
	GINCU_ACCESS_HACK(this->data->view, sfmlView_m_transform) = matrixToSfml(matrix);
	GINCU_ACCESS_HACK(this->data->view, sfmlView_m_inverseTransform) = matrixToSfml(inverseMatrix(matrix));
	GINCU_ACCESS_HACK(this->data->view, sfmlView_m_transformUpdated) = true;
	GINCU_ACCESS_HACK(this->data->view, sfmlView_m_invTransformUpdated) = true;

	const GSize windowSize = GApplication::getInstance()->getWindowSize();
	this->data->view.setViewport({
		this->viewport.x / windowSize.width,
		this->viewport.y / windowSize.height,
		this->viewport.width / windowSize.width,
		this->viewport.height / windowSize.height
	});
}

GPoint GCamera::mapScreenToCamera(const GPoint & point) const
{
	auto pt = GRenderEngine::getInstance()->getData()->window->mapPixelToCoords({(int)point.x, (int)point.y}, this->data->view);
	return {pt.x, pt.y};
}



} //namespace gincu

