#ifndef SCENETESTBED_H
#define SCENETESTBED_H

#include "gincu/gscene.h"

#include <memory>

class TestCase;
class TestBed;

class SceneTestBed : public gincu::GScene
{
public:
	static void switchToScene();

public:
	SceneTestBed();

private:
	virtual void doOnEnter() override;
	virtual void doOnExit() override;

private:
	std::unique_ptr<TestBed> testBed;
};


#endif
