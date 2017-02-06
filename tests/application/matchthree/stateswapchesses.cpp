#include "matchthree/stateswapchesses.h"
#include "matchthree/matchthreestates.h"
#include "matchthree/componentchess.h"
#include "matchthree/scenematchthree.h"
#include "matchthree/matchthreeboard.h"
#include "matchthree/matchthreechess.h"
#include "gincu/gstatemachine.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gentity.h"
#include "cpgf/tween/gtweenlist.h"
#include "cpgf/tween/easing/quad.h"
#include "cpgf/accessor/gaccessor.h"

namespace gincu {

StateSwapChesses::StateSwapChesses(SceneMatchThree * scene, const int stateId, const int nextStateId)
	: super(stateId, nextStateId), scene(scene)
{
}

StateSwapChesses::~StateSwapChesses()
{
}

void StateSwapChesses::doOnEnter()
{
	if(! this->doStartSwapChesses()) {
		this->getStateMachine()->gotoState(stateMainLoop);
	}
}

void StateSwapChesses::doOnExit()
{
}

bool StateSwapChesses::doStartSwapChesses()
{
	if(this->scene->getTouchedChessList().size() != 2) {
		return false;
	}

	Entity * chessA = this->scene->getTouchedChessList()[0];
	Entity * chessB = this->scene->getTouchedChessList()[1];
	RowColumn cellA = this->scene->getBoard()->getChessCell(chessA);
	RowColumn cellB = this->scene->getBoard()->getChessCell(chessB);

	if(! areCellsNeighbors(cellA, cellB)) {
		return false;
	}

	ComponentTransform * transformA = chessA->getComponentByType<ComponentTransform>();
	ComponentTransform * transformB = chessB->getComponentByType<ComponentTransform>();
	cpgf::GTweenList::getInstance()->tween()
		.duration(200.0f)
		.ease(cpgf::QuadEase::easeIn())
		.onComplete(cpgf::makeCallback(this, &StateSwapChesses::onSwapFinish))
		.target(cpgf::createAccessor(transformA, &ComponentTransform::getPosition, &ComponentTransform::setPosition), transformB->getPosition())
		.target(cpgf::createAccessor(transformB, &ComponentTransform::getPosition, &ComponentTransform::setPosition), transformA->getPosition())
	;

	return true;
}

void StateSwapChesses::onSwapFinish()
{
	Entity * chessA = this->scene->getTouchedChessList()[0];
	Entity * chessB = this->scene->getTouchedChessList()[1];
	RowColumn cellA = this->scene->getBoard()->getChessCell(chessA);
	RowColumn cellB = this->scene->getBoard()->getChessCell(chessB);
	this->scene->getBoard()->swapChess(cellA, chessB);
	this->scene->getBoard()->swapChess(cellB, chessA);

	this->finish();
}


} //namespace gincu
