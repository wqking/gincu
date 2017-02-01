#include "matchthree/scenematchthree.h"
#include "matchthree/matchthreeboard.h"
#include "matchthree/matchthreeinfoview.h"
#include "matchthree/matchthreechess.h"
#include "matchthree/matchthreeconsts.h"
#include "scenemenu.h"
#include "matchthree/matchthreestates.h"
#include "matchthree/componentchess.h"
#include "framework/statemachine.h"
#include "framework/entity.h"
#include "framework/componentrender.h"
#include "framework/componenttransform.h"
#include "framework/componenttouchhandler.h"
#include "framework/scenemanager.h"
#include "framework/util.h"
#include "framework/gameapplication.h"
#include "engine/touchevent.h"
#include "cpgf/tween/gtweenlist.h"
#include "cpgf/goutmain.h"

#include "matchthree/stateinitializenewround.h"
#include "matchthree/statecheckdeadboard.h"
#include "matchthree/statemainloop.h"
#include "matchthree/stateswapchesses.h"
#include "matchthree/stateerasematches.h"
#include "matchthree/stateresult.h"

namespace gincu {

SceneMatchThree::SceneMatchThree()
{
}

SceneMatchThree::~SceneMatchThree()
{
}

void SceneMatchThree::doOnEnter()
{
	this->addEntity(
		(new Entity())
			->addComponent(createComponent<ComponentTransform>())
			->addComponent(createAndLoadImageComponent(backgroundImageName))
	);
	this->addEntity(
		(new Entity())
			->addComponent(createComponent<ComponentTransform>(GamePoint { 10, GameApplication::getInstance()->getViewSize().height - 30 }))
			->addComponent(createComponent<ComponentContainerRender>()
				->add(createRectRenderComponent(0xffeeee77, GameSize{ 160, 60 }))
				->add(createAndLoadTextComponent("Quit game", colorBlue, normalFontSize))
			)
			->addComponent(createComponent<ComponentRendererTouchHandler>()->addOnTouch(cpgf::makeCallback(this, &SceneMatchThree::onQuitGameClicked)))
	);


	this->stateMachine.reset(new StateMachine());
	this->board.reset(new MatchThreeBoard(this));
	this->infoView.reset(new MatchThreeInfoView(this));

	this->stateMachine->registerState(new StateInitializeNewRound(this));
	this->stateMachine->registerState(new StateCheckDeadBoard(this));
	this->stateMachine->registerState(new StateMainLoop(this));
	this->stateMachine->registerState(new StateSwapChesses(this, stateSwapChesses, stateEraseMatches));
	this->stateMachine->registerState(new StateSwapChesses(this, stateSwapBackChesses, stateMainLoop));
	this->stateMachine->registerState(new StateEraseMatches(this, stateEraseMatches, stateSwapBackChesses));
	this->stateMachine->registerState(new StateEraseMatches(this, stateCheckEraseMatches, stateCheckDeadBoard));
	this->stateMachine->registerState(new StateResult(this));

	this->stateMachine->gotoState(stateInitializeNewRound);

	this->roundStartMilliseconds = getMilliseconds();

	GameApplication::getInstance()->addUpdater(cpgf::makeCallback(this, &SceneMatchThree::onUpdate));

	this->infoView->setRemainingSeconds(secondsPerRound);
}

void SceneMatchThree::doOnExit()
{
	GameApplication::getInstance()->removeUpdater(cpgf::makeCallback(this, &SceneMatchThree::onUpdate));

	cpgf::GTweenList::getInstance()->clear();
}

void SceneMatchThree::clearTouchedChessList()
{
	this->touchedChessList.clear();
}

void SceneMatchThree::restoreTouchedChessList()
{
	for(auto it = this->touchedChessList.begin(); it != this->touchedChessList.end(); ++it) {
		(*it)->getComponentByType<ComponentTransform>()->setScale(1.0f);
	}
}

void SceneMatchThree::onUpdate()
{
	this->infoView->setRemainingSeconds(secondsPerRound - (getMilliseconds() - this->roundStartMilliseconds) / 1000);

	if(this->isTimeUp()) {
		if(this->stateMachine->getCurrentStateId() == stateMainLoop) {
			this->stateMachine->gotoState(stateResult);
		}
	}
}

void SceneMatchThree::onQuitGameClicked(const TouchEvent & touchEvent)
{
	if(touchEvent.type == TouchEventType::eventPressed) {
		this->roundStartMilliseconds = getMilliseconds() - secondsPerRound * 1000;
	}
}

void SceneMatchThree::onChessTouched(const TouchEvent & touchEvent)
{
	if(this->stateMachine->getCurrentStateId() != stateMainLoop || isTimeUp()) {
		return;
	}

	switch(touchEvent.type) {
	case TouchEventType::eventPressed:
		if(touchEvent.touchedEntity == nullptr || touchEvent.touchedEntity->getComponentByType<ComponentChess>() == nullptr) {
			this->restoreTouchedChessList();
			this->clearTouchedChessList();
		}
		else {
			if(this->touchedChessList.size() == 1) {
				Entity * chessA = touchedChessList[0];
				RowColumn cellA = board->getChessCell(chessA);
				RowColumn cellB = board->getChessCell(touchEvent.touchedEntity);

				if(chessA == touchEvent.touchedEntity || ! areCellsNeighbors(cellA, cellB)) {
					this->restoreTouchedChessList();
					this->clearTouchedChessList();
				}

				if(chessA == touchEvent.touchedEntity) {
					break;
				}
			}
			if(this->touchedChessList.empty()) {
				touchEvent.touchedEntity->getComponentByType<ComponentTransform>()->setScale(1.2f);
			}

			this->touchedChessList.push_back(touchEvent.touchedEntity);
			this->setTouchCapture(touchEvent.touchedEntity);
		}
		break;

	case TouchEventType::eventReleased:
		if(touchEvent.touchedEntity == nullptr || touchEvent.touchedEntity->getComponentByType<ComponentChess>() == nullptr) {
			this->restoreTouchedChessList();
			this->clearTouchedChessList();
		}
		else {
			if(! this->touchedChessList.empty()) {
				if(this->touchedChessList.back() != touchEvent.touchedEntity) {
					this->touchedChessList.push_back(touchEvent.touchedEntity);
					this->setTouchCapture(nullptr);
				}
			}
		}
		break;

	case TouchEventType::eventMoved:
		break;
	}

	if(this->touchedChessList.size() == 2) {
		this->setTouchCapture(nullptr);
		this->restoreTouchedChessList();
		this->stateMachine->gotoState(stateSwapChesses);
	}
}

void SceneMatchThree::gotScore(const int score)
{
	this->infoView->addScore(score);
}

int SceneMatchThree::getTotalScore() const
{
	return this->infoView->getTotalScore();
}

bool SceneMatchThree::isTimeUp() const
{
	return this->infoView->getRemainingSeconds() <= 0;
}


G_AUTO_RUN_BEFORE_MAIN()
{
	MenuRegister::getInstance()->registerItem("match three", 1, [](){
			GameApplication::getInstance()->getSceneManager()->switchScene(new SceneMatchThree());
		},
		0xffeeee77);
}


} //namespace gincu
