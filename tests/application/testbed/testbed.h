#ifndef TESTBED_H
#define TESTBED_H

#include "cpgf/gcallback.h"

#include <string>
#include <vector>
#include <memory>

class TestCase;
class SceneTestCase;

class TestBed
{
public:
	TestBed();
	~TestBed();

	void executeTestCase(TestCase * testCase);
	void finishTestCase();

	void print(const std::string & message) const;

	SceneTestCase * getScene() const { return this->scene; }

private:
	std::unique_ptr<TestCase> testCase;
	SceneTestCase * scene;
};

struct TestCaseItem
{
	std::string caption;
	cpgf::GCallback<TestCase * ()> creator;
};

class TestBedRegister
{
public:
	static TestBedRegister * getInstance();

public:
	void registerItem(const std::string & caption, const cpgf::GCallback<TestCase * ()> & creator);
	const std::vector<TestCaseItem> & getSortedItemList() const;

private:
	void sortItemList() const;

private:
	mutable std::vector<TestCaseItem> itemList;
};



#endif
