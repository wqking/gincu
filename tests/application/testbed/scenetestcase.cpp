#include "scenetestcase.h"
#include "testcase.h"
#include "testbed.h"
#include "uiutil.h"

SceneTestCase::SceneTestCase(TestCase * testCase)
	: testCase(testCase)
{
}

void SceneTestCase::doOnEnter()
{
	this->addEntity(createBackButton([=]() {
		this->testCase->getTestBed()->finishTestCase();
	}));
}

void SceneTestCase::doOnExit()
{
}

