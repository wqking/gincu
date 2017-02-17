#ifndef GSCENE_H
#define GSCENE_H

#include "gincu/ggeometry.h"

#include "cpgf/tween/gtweenlist.h"

#include <memory>
#include <vector>

namespace gincu {

class GComponentManager;
class GEntity;
class GComponentCamera;
class GEvent;

class GScene
{
private:
	typedef std::unique_ptr<GEntity> EntityPointer;

public:
	GScene();
	virtual ~GScene();

	void onEnter();
	void onExit();

	void renderScene();

	void handleTouchEvent(const GEvent & touchEvent);

	GEntity * addEntity(GEntity * entity);
	void removeEntity(GEntity * entity);

	void setTouchCapture(GEntity * touchCapture);
	GEntity * getTouchCapture() const;

	GComponentCamera * getPrimaryCamera() const { return this->primaryCamera; }

	cpgf::GTweenList * getTweenList() { return &this->tweenList; }

private:
	void initializePrimaryCamera();

private:
	virtual void doOnEnter();
	virtual void doOnExit();

private:
	std::unique_ptr<GComponentManager> componentManager;
	std::vector<EntityPointer> entityList;
	GComponentCamera * primaryCamera;
	GEntity * touchCapture;
	cpgf::GTweenList tweenList;
};


template <typename T>
T * sceneCreator()
{
	return new T();
}

cpgf::GTweenList * getTweenListFromScene();


} //namespace gincu

#endif

