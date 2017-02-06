#ifndef SCENELOGO_H
#define SCENELOGO_H

#include "gincu/gscene.h"

namespace gincu {

struct GTouchEvent;

class SceneLogo : public GScene
{
public:
	explicit SceneLogo(const bool showProgressBar);
	~SceneLogo();

private:
	void doExitLogo();
	void onPressAnyKey(const GTouchEvent & touchEvent);

private:
	virtual void doOnEnter() override;
	virtual void doOnExit() override;

private:
	bool showProgressBar;
};


} //namespace gincu


#endif
