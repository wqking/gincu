#ifndef SCENETESTCASE_H
#define SCENETESTCASE_H

#include "gincu/gscene.h"

class TestBed;
class TestCase;

class SceneTestCase : public gincu::GScene
{
public:
	SceneTestCase(TestBed * testBed, TestCase * testCase);

private:
	virtual void doOnEnter() override;
	virtual void doOnExit() override;

private:
	TestBed * testBed;
	TestCase * testCase;
};


#endif
