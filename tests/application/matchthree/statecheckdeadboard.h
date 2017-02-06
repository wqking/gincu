#ifndef STATECHECKDEADBOARD_H
#define STATECHECKDEADBOARD_H

#include "gincu/gstate.h"

namespace gincu {

class SceneMatchThree;

class StateCheckDeadBoard : public GState
{
private:
	typedef GState super;

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
