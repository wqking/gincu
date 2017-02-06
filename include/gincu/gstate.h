#ifndef GSTATE_H
#define GSTATE_H

namespace gincu {

const int invalidStateId = -1;

class StateMachine;

// we don't provide update() function here,
// we can always use GameApplication::addUpdater to add an updater.
class State
{
public:
	State(const int id, const int nextId = invalidStateId);
	virtual ~State();

	void onEnter();
	void onExit();

	void finish();
	void gotoNext();

	int getId() const { return id; }
	int getNextId() const { return nextId; }

	StateMachine * getStateMachine() const { return stateMachine; }

private:
	virtual void doOnEnter();
	virtual void doOnExit();

private:
	int id;
	int nextId;
	StateMachine * stateMachine;

private:
	friend class StateMachine;
};


} //namespace gincu

#endif
