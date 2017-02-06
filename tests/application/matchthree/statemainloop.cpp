#include "matchthree/statemainloop.h"
#include "matchthree/matchthreestates.h"
#include "matchthree/matchthreeboard.h"
#include "matchthree/matchthreechess.h"
#include "matchthree/componentchess.h"
#include "matchthree/scenematchthree.h"

namespace gincu {

StateMainLoop::StateMainLoop(SceneMatchThree * scene)
	: super(stateMainLoop), scene(scene)
{

}

StateMainLoop::~StateMainLoop()
{
}

void StateMainLoop::doOnEnter()
{
	this->scene->clearTouchedChessList();
}

void StateMainLoop::doOnExit()
{
}


} //namespace gincu
