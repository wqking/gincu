#ifndef SCENETESTCASE_H
#define SCENETESTCASE_H

#include "gincu/gscene.h"

class TestCase;

class SceneTestCase : public gincu::GScene
{
public:
	explicit SceneTestCase(TestCase * testCase);

private:
	virtual void doOnEnter() override;
	virtual void doOnExit() override;

private:
	TestCase * testCase;
};


#endif
