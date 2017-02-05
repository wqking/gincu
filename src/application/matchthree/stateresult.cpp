#include "matchthree/stateresult.h"
#include "matchthree/matchthreestates.h"
#include "matchthree/matchthreeboard.h"
#include "matchthree/scenematchthree.h"
#include "scenemenu.h"
#include "matchthree/matchthreeconsts.h"
#include "framework/gameapplication.h"
#include "engine/touchevent.h"
#include "framework/entity.h"
#include "framework/componentrender.h"
#include "framework/componenttransform.h"
#include "framework/componenttouchhandler.h"
#include "framework/componentanchor.h"
#include "framework/scenemanager.h"
#include "framework/util.h"
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
	this->scene->removeEntity(this->textEntity);
}

void StateResult::onBackgroundShown()
{
	this->textEntity->addComponent(createComponent<ComponentRendererTouchHandler>()->addOnTouch(cpgf::makeCallback(this, &StateResult::onFinish)));
	this->scene->setTouchCapture(this->textEntity);
}

void StateResult::onFinish(const TouchEvent & touchEvent)
{
	if(touchEvent.type == TouchEventType::eventPressed) {
		SceneMenu::returnToMainMenu();
		this->gotoNext();
	}
}

void StateResult::doCollectChesses()
{
	MatchThreeBoard * board = this->scene->getBoard();

	const GameApplication * application = GameApplication::getInstance();

	cpgf::GTween & tween = cpgf::GTweenList::getInstance()->tween()
		.duration(600)
		.ease(cpgf::QuadEase::easeIn())
		.onComplete(cpgf::makeCallback(this, &StateResult::doShowMessage))
	;

	const int rowCount = board->getRowCount();
	const int columnCount = board->getColumnCount();

	for(int row = 0; row < rowCount; ++row) {
		for(int column = 0; column < columnCount; ++column) {
			const RowColumn rowColumn { row, column };

			Entity * chess = board->getChessAt(rowColumn);

			ComponentTransform * transform = chess->getComponentByType<ComponentTransform>();

			CoordType x = 0;
			CoordType y = 0;
			if(getRand(2) == 0) {
				x = (getRand(2) == 0 ? -getRand(50, 100) : application->getViewSize().width + getRand(50, 100));
				y = (CoordType)getRand((int)application->getViewSize().height);
			}
			else {
				x = (CoordType)getRand((int)application->getViewSize().width);
				y = (CoordType)(getRand(2) == 0 ? -getRand(50, 100) : application->getViewSize().height + getRand(50, 100));
			}
			tween.target(cpgf::createAccessor(transform, &ComponentTransform::getPosition, &ComponentTransform::setPosition), GamePoint{x, y});
		}
	}
}

void StateResult::doShowMessage()
{
	const GameApplication * application = GameApplication::getInstance();

	this->backgroundEntity = this->scene->addEntity(
		(new Entity())
		->addComponent(createComponent<ComponentTransform>())
		->addComponent(createComponent<ComponentLocalTransform>(GamePoint { application->getViewSize().width / 2, application->getViewSize().height / 2 }, GameScale { 0.1f, 0.1f }))
		->addComponent(createComponent<ComponentAnchor>(RenderAnchor_Center))
		->addComponent(createRectRenderComponent(gameColorSetAlpha(colorGreen, 127), GameSize { 450, 200}))
		);

	this->textEntity = this->scene->addEntity(
		(new Entity())
		->addComponent(createComponent<ComponentTransform>())
		->addComponent(createComponent<ComponentLocalTransform>(GamePoint{ 0, 0 })->setParent(this->backgroundEntity->getComponentByType<ComponentLocalTransform>()))
		->addComponent(createComponent<ComponentAnchor>(RenderAnchor_Center))
		->addComponent(createAndLoadTextComponent("Great! Your score is " + toString(scene->getTotalScore()), colorWhite, normalFontSize))
		);

	ComponentLocalTransform * transform = backgroundEntity->getComponentByType<ComponentLocalTransform>();
	cpgf::GTweenList::getInstance()->tween()
		.duration(1000)
		.ease(cpgf::ElasticEase::easeOut())
		.onComplete(cpgf::makeCallback(this, &StateResult::onBackgroundShown))
		.target(cpgf::createAccessor(transform, &ComponentLocalTransform::getScale, &ComponentLocalTransform::setScale), GameScale { 1.0f, 1.0f })
	;
}


} //namespace gincu
