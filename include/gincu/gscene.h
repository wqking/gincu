#ifndef GSCENE_H
#define GSCENE_H

#include "gincu/ggeometry.h"
#include "gincu/gcomponentsbuffer.h"

#include <memory>
#include <vector>

namespace gincu {

class GEntity;
struct GTouchEvent;

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

	void handleTouchEvent(const GTouchEvent & touchEvent);

	GEntity * addEntity(GEntity * entity);
	void removeEntity(GEntity * entity);

	void setTouchCapture(GEntity * touchCapture);
	GEntity * getTouchCapture() const;

private:
	virtual void doOnEnter();
	virtual void doOnExit();

private:
	GComponentsBuffer componentsBuffer;
	std::vector<EntityPointer> entityList;
	GEntity * touchCapture;
};


template <typename T>
T * sceneCreator()
{
	return new T();
}


} //namespace gincu

#endif

