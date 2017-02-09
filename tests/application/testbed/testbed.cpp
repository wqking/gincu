#include "testbed.h"
#include "testcase.h"
#include "scenetestcase.h"
#include "scenetestbed.h"
#include "gincu/gapplication.h"
#include "gincu/gscenemanager.h"
#include "gincu/glog.h"

using namespace gincu;

TestBed::TestBed()
	: testCase(nullptr), scene(nullptr)
{
}

TestBed::~TestBed()
{
}

void TestBed::executeTestCase(TestCase * testCase)
{
	this->testCase.reset(testCase);
	this->scene = new SceneTestCase(this, this->testCase.get());

	GApplication::getInstance()->getSceneManager()->switchScene(this->scene);
}

void TestBed::finishTestCase()
{
	this->scene = nullptr;
	SceneTestBed::switchToScene();
}

void TestBed::print(const std::string & message) const
{
	G_LOG_INFO(message.c_str());
}


TestBedRegister * TestBedRegister::getInstance()
{
	static TestBedRegister instance;

	return &instance;
}

void TestBedRegister::registerItem(const std::string & caption, const cpgf::GCallback<TestCase * ()> & creator)
{
	this->itemList.push_back({
		caption,
		creator
	});
}

const std::vector<TestCaseItem> & TestBedRegister::getSortedItemList() const
{
	this->sortItemList();
	return this->itemList;
}

void TestBedRegister::sortItemList() const
{
	std::sort(this->itemList.begin(), this->itemList.end(), [](const TestCaseItem & a, const TestCaseItem & b) { return a.caption < b.caption; });
}

