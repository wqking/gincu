#include "matchthree/stateresult.h"
#include "matchthree/matchthreestates.h"
#include "matchthree/matchthreeboard.h"
#include "matchthree/scenematchthree.h"
#include "scenemenu.h"
#include "matchthree/matchthreeconsts.h"
#include "gincu/gapplication.h"
#include "gincu/gevent.h"
#include "gincu/gentity.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/gcomponentanchor.h"
#include "gincu/gcomponentcamera.h"
#include "gincu/gscenemanager.h"
#include "gincu/gutil.h"
#include "cpgf/tween/gtweenlist.h"
#include "cpgf/tween/easing/elastic.h"
#include "cpgf/tween/easing/quad.h"
#include "cpgf/accessor/gaccessor.h"

namespace gincu {

StateResult::StateResult(SceneMatchThree * scene)
	:
		super(stateResult),
		scene(scene),
		backgroundEntity(nullptr),
		textEntity(nullptr)
{

}

StateResult::~StateResult()
{

}

void StateResult::doOnEnter()
{
	this->doCollectChesses();
}

void StateResult::doOnExit()
{
	this->scene->setTouchCapture(nullptr);
	this->scene->removeEntity(this->backgroundEntity);
	this->scene->removeEntity(this->imageEntity);
	this->scene->removeEntity(this->textEntity);
}

void StateResult::onBackgroundShown()
{
	this->textEntity->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(cpgf::makeCallback(this, &StateResult::onFinish)));
	this->scene->setTouchCapture(this->textEntity);
}

void StateResult::onFinish(const GEvent & touchEvent)
{
	if(touchEvent.type == GEventType::touchPressed) {
		SceneMenu::returnToMainMenu();
		this->gotoNext();
	}
}

void StateResult::doCollectChesses()
{
	MatchThreeBoard * board = this->scene->getBoard();

	cpgf::GTween & tween = getTweenListFromScene()->tween()
		.duration(600)
		.ease(cpgf::QuadEase::easeIn())
		.onComplete(cpgf::makeCallback(this, &StateResult::doShowMessage))
	;

	const int rowCount = board->getRowCount();
	const int columnCount = board->getColumnCount();
	
	const GSize viewSize = this->scene->getPrimaryCamera()->getWorldSize();

	for(int row = 0; row < rowCount; ++row) {
		for(int column = 0; column < columnCount; ++column) {
			const RowColumn rowColumn { row, column };

			GEntity * chess = board->getChessAt(rowColumn);

			GComponentTransform * transform = chess->getComponentByType<GComponentTransform>();

			GCoord x = 0;
			GCoord y = 0;
			if(getRand(2) == 0) {
				x = (getRand(2) == 0 ? -getRand(50, 100) : viewSize.width + getRand(50, 100));
				y = (GCoord)getRand((int)viewSize.height);
			}
			else {
				x = (GCoord)getRand((int)viewSize.width);
				y = (GCoord)(getRand(2) == 0 ? -getRand(50, 100) : viewSize.height + getRand(50, 100));
			}
			tween.target(cpgf::createAccessor(transform, &GComponentTransform::getPosition, &GComponentTransform::setPosition), GPoint{x, y});
		}
	}
}

void StateResult::doShowMessage()
{
	const GSize viewSize = this->scene->getPrimaryCamera()->getWorldSize();

	this->backgroundEntity = this->scene->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>())
		->addComponent(createComponent<GComponentLocalTransform>(GPoint { viewSize.width / 2, viewSize.height / 2 }, GScale { 0.1f, 0.1f }))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
		->addComponent(createRectRenderComponent(gameColorSetAlpha(colorGreen, 127), GSize { 450, 200}))
		);

	this->imageEntity = this->scene->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>())
		->addComponent(createComponent<GComponentLocalTransform>(GPoint{ 0, 0 }, GScale{ 0.2f, 0.2f })->setParent(this->backgroundEntity->getComponentByType<GComponentLocalTransform>()))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center)->setFlipX(true)->setFlipY(true))
		->addComponent(createAndLoadImageComponent(backgroundImageName))
	);

	this->textEntity = this->scene->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>())
		->addComponent(createComponent<GComponentLocalTransform>(GPoint{ 0, 0 })->setParent(this->backgroundEntity->getComponentByType<GComponentLocalTransform>()))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
		->addComponent(createAndLoadTextComponent("Great! Your score is " + toString(scene->getTotalScore()), colorWhite, normalFontSize))
		);

	GComponentLocalTransform * transform = backgroundEntity->getComponentByType<GComponentLocalTransform>();
	getTweenListFromScene()->tween()
		.duration(1000)
		.ease(cpgf::ElasticEase::easeOut())
		.onComplete(cpgf::makeCallback(this, &StateResult::onBackgroundShown))
		.target(cpgf::createAccessor(transform, &GComponentLocalTransform::getScale, &GComponentLocalTransform::setScale), GScale { 1.0f, 1.0f })
		.target(cpgf::createAccessor(transform, &GComponentLocalTransform::getRotation, &GComponentLocalTransform::setRotation), 360)
	;
}


} //namespace gincu
