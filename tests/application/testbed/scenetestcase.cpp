#include "scenetestcase.h"
#include "testcase.h"
#include "testbed.h"
#include "uiutil.h"

SceneTestCase::SceneTestCase(TestBed * testBed, TestCase * testCase)
	: testBed(testBed), testCase(testCase)
{
}

void SceneTestCase::doOnEnter()
{
	this->testCase->initialize(this->testBed);

	this->addEntity(createBackButton([=]() {
		this->testCase->getTestBed()->finishTestCase();
	}));
}

void SceneTestCase::doOnExit()
{
	this->testCase->finalize();
}

