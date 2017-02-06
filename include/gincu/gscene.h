#ifndef GSCENE_H
#define GSCENE_H

#include "gincu/ggeometry.h"
#include "gincu/gcomponentsbuffer.h"

#include <memory>
#include <vector>

namespace gincu {

class Entity;
struct TouchEvent;

class Scene
{
private:
	typedef std::unique_ptr<Entity> EntityPointer;

public:
	Scene();
	virtual ~Scene();

	void onEnter();
	void onExit();

	void renderScene();

	void handleTouchEvent(const TouchEvent & touchEvent);

	Entity * addEntity(Entity * entity);
	void removeEntity(Entity * entity);

	void setTouchCapture(Entity * touchCapture);
	Entity * getTouchCapture() const;

private:
	virtual void doOnEnter();
	virtual void doOnExit();

private:
	ComponentsBuffer componentsBuffer;
	std::vector<EntityPointer> entityList;
	Entity * touchCapture;
};


} //namespace gincu

#endif

