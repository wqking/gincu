#include "gincu/gstatemachine.h"
#include "gincu/gstate.h"
#include "gincu/gutil.h"
#include "gincu/gerrorhandler.h"

namespace gincu {

GStateMachine::GStateMachine()
	:
		stateMap(),
		currentState(nullptr)
{
}

GStateMachine::~GStateMachine()
{
}

void GStateMachine::registerState(GState * state)
{
	state->stateMachine = this;
	this->stateMap[state->getId()].reset(state);
}

int GStateMachine::getCurrentStateId() const
{
	if(this->currentState == nullptr) {
		return invalidStateId;
	}
	else {
		return this->currentState->getId();
	}
}

void GStateMachine::gotoState(const int stateId)
{
	GState * nextState = nullptr;

	if(stateId != invalidStateId) {
		auto it = this->stateMap.find(stateId);
		if(it == this->stateMap.end()) {
			handleFatal("Can't find state id: " + toString(stateId));
			return;
		}
		nextState = it->second.get();
	}

	if(this->currentState != nullptr) {
		this->currentState->onExit();
	}

	this->currentState = nextState;

	if(this->currentState != nullptr) {
		this->currentState->onEnter();
	}
}


} //namespace gincu
