#include "gincu/gstate.h"
#include "gincu/gstatemachine.h"

namespace gincu {

GState::GState(const int id, const int nextId)
	: id(id), nextId(nextId), stateMachine(nullptr)
{
}

GState::~GState()
{
}

void GState::onEnter()
{
	this->doOnEnter();
}

void GState::onExit()
{
	this->doOnExit();
}

void GState::doOnEnter()
{
}

void GState::doOnExit()
{
}

void GState::finish()
{
	this->gotoNext();
}

void GState::gotoNext()
{
	this->getStateMachine()->gotoState(this->getNextId());
}


} //namespace gincu
