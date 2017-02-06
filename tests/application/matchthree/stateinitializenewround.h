#ifndef STATEINITIALIZENEWROUND_H
#define STATEINITIALIZENEWROUND_H

#include "gincu/gstate.h"

namespace gincu {

class SceneMatchThree;

class StateInitializeNewRound : public State
{
private:
	typedef State super;

public:
	explicit StateInitializeNewRound(SceneMatchThree * scene);
	~StateInitializeNewRound();

private:
	virtual void doOnEnter() override;
	virtual void doOnExit() override;

private:
	SceneMatchThree * scene;
};


} //namespace gincu

#endif
