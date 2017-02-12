#ifndef GSCENE_H
#define GSCENE_H

#include "gincu/ggeometry.h"
#include "gincu/gcomponentmanager.h"

#include "cpgf/tween/gtweenlist.h"

#include <memory>
#include <vector>

namespace gincu {

class GEntity;
struct GEvent;

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
	void removeAllEntities();

	void setTouchCapture(GEntity * touchCapture);
	GEntity * getTouchCapture() const;

	cpgf::GTweenList * getTweenList() { return &this->tweenList; }

private:
	virtual void doOnEnter();
	virtual void doOnExit();

private:
	GComponentManager componentManager;
	std::vector<EntityPointer> entityList;
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

