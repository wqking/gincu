#ifndef TESTCASE_H
#define TESTCASE_H

class TestBed;
class SceneTestCase;

class TestCase
{
public:
	TestCase();
	virtual ~TestCase();

	void initialize(TestBed * testBed);
	void finalize();

	SceneTestCase * getScene() const;
	TestBed * getTestBed() const { return this->testBed; }

private:
	virtual void doInitialize();
	virtual void doFinalize();

private:
	TestBed * testBed;
};

template <typename T>
T * testCaseCreator()
{
	return new T();
}


#endif
