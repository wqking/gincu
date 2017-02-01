#ifndef STATECHECKDEADBOARD_H
#define STATECHECKDEADBOARD_H

#include "framework/state.h"

namespace gincu {

class SceneMatchThree;

class StateCheckDeadBoard : public State
{
private:
	typedef State super;

public:
	explicit StateCheckDeadBoard(SceneMatchThree * scene);
	~StateCheckDeadBoard();

private:
	virtual void doOnEnter() override;
	virtual void doOnExit() override;

private:
	SceneMatchThree * scene;
};


} //namespace gincu

#endif
