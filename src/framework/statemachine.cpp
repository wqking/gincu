#include "framework/statemachine.h"
#include "framework/state.h"
#include "framework/util.h"
#include "engine/errorhandler.h"

namespace gincu {

StateMachine::StateMachine()
	:
		stateMap(),
		currentState(nullptr)
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::registerState(State * state)
{
	state->stateMachine = this;
	this->stateMap[state->getId()].reset(state);
}

int StateMachine::getCurrentStateId() const
{
	if(this->currentState == nullptr) {
		return invalidStateId;
	}
	else {
		return this->currentState->getId();
	}
}

void StateMachine::gotoState(const int stateId)
{
	State * nextState = nullptr;

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
