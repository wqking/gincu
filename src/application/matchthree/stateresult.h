#ifndef STATERESULT_H
#define STATERESULT_H

#include "framework/state.h"

namespace gincu {

class SceneMatchThree;
class Entity;
struct TouchEvent;

class StateResult : public State
{
private:
	typedef State super;

public:
	explicit StateResult(SceneMatchThree * scene);
	~StateResult();

private:
	void onBackgroundShown();
	void onFinish(const TouchEvent & touchEvent);
	void doCollectChesses();
	void doShowMessage();

private:
	virtual void doOnEnter() override;
	virtual void doOnExit() override;

private:
	SceneMatchThree * scene;
	Entity * backgroundEntity;
	Entity * textEntity;
};


} //namespace gincu

#endif
