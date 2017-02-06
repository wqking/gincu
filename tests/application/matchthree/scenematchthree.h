#ifndef SCENEMATCHTHREE_H
#define SCENEMATCHTHREE_H

#include "gincu/gscene.h"
#include "gincu/ggeometry.h"

#include <memory>
#include <vector>

namespace gincu {

class MatchThreeBoard;
class MatchThreeInfoView;
class StateMachine;
struct TouchEvent;

class SceneMatchThree : public Scene
{
public:
	SceneMatchThree();
	~SceneMatchThree();

	void onChessTouched(const TouchEvent & touchEvent);

	void clearTouchedChessList();

	void gotScore(const int score);

	int getTotalScore() const;

	MatchThreeBoard * getBoard() const { return board.get(); }
	const std::vector<Entity *> & getTouchedChessList() const { return touchedChessList; }

private:
	void onUpdate();
	void onQuitGameClicked(const TouchEvent & touchEvent);
	void restoreTouchedChessList();
	bool isTimeUp() const;

private:
	virtual void doOnEnter() override;
	virtual void doOnExit() override;

private:
	std::unique_ptr<StateMachine> stateMachine;
	std::unique_ptr<MatchThreeBoard> board;
	std::unique_ptr<MatchThreeInfoView> infoView;
	std::vector<Entity *> touchedChessList;

	GamePoint previousTouchPosition;

	unsigned int roundStartMilliseconds;
};


} //namespace gincu


#endif
