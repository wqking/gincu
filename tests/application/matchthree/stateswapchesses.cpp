#include "matchthree/stateswapchesses.h"
#include "matchthree/matchthreestates.h"
#include "matchthree/componentchess.h"
#include "matchthree/scenematchthree.h"
#include "matchthree/matchthreeboard.h"
#include "matchthree/matchthreechess.h"
#include "gincu/gstatemachine.h"
#include "gincu/ecs/gcomponenttransform.h"
#include "gincu/ecs/gentity.h"
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

	GEntity * chessA = this->scene->getTouchedChessList()[0];
	GEntity * chessB = this->scene->getTouchedChessList()[1];
	RowColumn cellA = this->scene->getBoard()->getChessCell(chessA);
	RowColumn cellB = this->scene->getBoard()->getChessCell(chessB);

	if(! areCellsNeighbors(cellA, cellB)) {
		return false;
	}

	GComponentTransform * transformA = chessA->getComponentByType<GComponentTransform>();
	GComponentTransform * transformB = chessB->getComponentByType<GComponentTransform>();
	this->scene->getTweenList()->tween()
		.duration(200.0f)
		.ease(cpgf::QuadEase::easeIn())
		.onComplete(cpgf::makeCallback(this, &StateSwapChesses::onSwapFinish))
		.target(cpgf::createAccessor(transformA, &GComponentTransform::getPosition, &GComponentTransform::setPosition), transformB->getPosition())
		.target(cpgf::createAccessor(transformB, &GComponentTransform::getPosition, &GComponentTransform::setPosition), transformA->getPosition())
	;

	return true;
}

void StateSwapChesses::onSwapFinish()
{
	GEntity * chessA = this->scene->getTouchedChessList()[0];
	GEntity * chessB = this->scene->getTouchedChessList()[1];
	RowColumn cellA = this->scene->getBoard()->getChessCell(chessA);
	RowColumn cellB = this->scene->getBoard()->getChessCell(chessB);
	this->scene->getBoard()->swapChess(cellA, chessB);
	this->scene->getBoard()->swapChess(cellB, chessA);

	this->finish();
}


} //namespace gincu
