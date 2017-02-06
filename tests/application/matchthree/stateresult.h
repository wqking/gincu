#ifndef STATERESULT_H
#define STATERESULT_H

#include "gincu/gstate.h"

namespace gincu {

class SceneMatchThree;
class GEntity;
struct GTouchEvent;

class StateResult : public GState
{
private:
	typedef GState super;

public:
	explicit StateResult(SceneMatchThree * scene);
	~StateResult();

private:
	void onBackgroundShown();
	void onFinish(const GTouchEvent & touchEvent);
	void doCollectChesses();
	void doShowMessage();

private:
	virtual void doOnEnter() override;
	virtual void doOnExit() override;

private:
	SceneMatchThree * scene;
	GEntity * backgroundEntity;
	GEntity * imageEntity;
	GEntity * textEntity;
};


} //namespace gincu

#endif
