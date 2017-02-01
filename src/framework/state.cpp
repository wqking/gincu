#include "framework/state.h"
#include "framework/statemachine.h"

namespace gincu {

State::State(const int id, const int nextId)
	: id(id), nextId(nextId), stateMachine(nullptr)
{
}

State::~State()
{
}

void State::onEnter()
{
	this->doOnEnter();
}

void State::onExit()
{
	this->doOnExit();
}

void State::doOnEnter()
{
}

void State::doOnExit()
{
}

void State::finish()
{
	this->gotoNext();
}

void State::gotoNext()
{
	this->getStateMachine()->gotoState(this->getNextId());
}


} //namespace gincu
