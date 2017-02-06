#ifndef GSTATEMACHINE_H
#define GSTATEMACHINE_H

#include <memory>
#include <map>

namespace gincu {

class GState;

class GStateMachine
{
public:
	GStateMachine();
	~GStateMachine();

	void gotoState(const int stateId);

	void registerState(GState * state);

	int getCurrentStateId() const;

	GState * getCurrentState() const { return currentState; }

private:
	std::map<int, std::shared_ptr<GState> > stateMap;
	GState * currentState;
};


} //namespace gincu

#endif
