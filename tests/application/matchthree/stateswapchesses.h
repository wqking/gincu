#ifndef STATESWAPCHESSES_H
#define STATESWAPCHESSES_H

#include "gincu/gstate.h"

namespace gincu {

class SceneMatchThree;

class StateSwapChesses : public State
{
private:
	typedef State super;

public:
	StateSwapChesses(SceneMatchThree * scene, const int stateId, const int nextStateId);
	~StateSwapChesses();

private:
	bool doStartSwapChesses();
	void onSwapFinish();

private:
	virtual void doOnEnter() override;
	virtual void doOnExit() override;

private:
	SceneMatchThree * scene;
};


} //namespace gincu

#endif
