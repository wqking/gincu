#ifndef STATEMAINLOOP_H
#define STATEMAINLOOP_H

#include "gincu/gstate.h"

namespace gincu {

class SceneMatchThree;

class StateMainLoop : public State
{
private:
	typedef State super;

public:
	explicit StateMainLoop(SceneMatchThree * scene);
	~StateMainLoop();

private:
	virtual void doOnEnter() override;
	virtual void doOnExit() override;

private:
	SceneMatchThree * scene;
};


} //namespace gincu

#endif
