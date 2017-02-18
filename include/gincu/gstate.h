#ifndef GSTATE_H
#define GSTATE_H

namespace gincu {

const int invalidStateId = -1;

class GStateMachine;

class GState
{
public:
	GState(const int id, const int nextId = invalidStateId);
	virtual ~GState();

	void onEnter();
	void onExit();

	void finish();
	void gotoNext();

	int getId() const { return id; }
	int getNextId() const { return nextId; }

	GStateMachine * getStateMachine() const { return stateMachine; }

private:
	virtual void doOnEnter();
	virtual void doOnExit();

private:
	int id;
	int nextId;
	GStateMachine * stateMachine;

private:
	friend class GStateMachine;
};


} //namespace gincu

#endif
