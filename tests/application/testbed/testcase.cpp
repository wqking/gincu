#include "testcase.h"
#include "testbed.h"
#include "scenetestcase.h"
#include "gincu/gapplication.h"
#include "gincu/gscenemanager.h"

using namespace gincu;

TestCase::TestCase()
	:
		testBed(nullptr)
{
}

TestCase::~TestCase()
{
}

SceneTestCase * TestCase::getScene() const
{
	return this->getTestBed()->getScene();
}

void TestCase::initialize(TestBed * testBed)
{
	this->testBed = testBed;

	this->doInitialize();
}

void TestCase::finalize()
{
	this->doFinalize();
}

void TestCase::doInitialize()
{
}

void TestCase::doFinalize()
{
}


