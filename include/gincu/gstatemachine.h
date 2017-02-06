#ifndef GSTATEMACHINE_H
#define GSTATEMACHINE_H

#include <memory>
#include <map>

namespace gincu {

class State;

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void gotoState(const int stateId);

	void registerState(State * state);

	int getCurrentStateId() const;

	State * getCurrentState() const { return currentState; }

private:
	std::map<int, std::shared_ptr<State> > stateMap;
	State * currentState;
};


} //namespace gincu

#endif
