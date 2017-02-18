#ifndef SCENEMATCHTHREE_H
#define SCENEMATCHTHREE_H

#include "gincu/gscene.h"
#include "gincu/ggeometry.h"

#include <memory>
#include <vector>

namespace gincu {

class MatchThreeBoard;
class MatchThreeInfoView;
class GStateMachine;
class GEvent;

class SceneMatchThree : public GScene
{
public:
	SceneMatchThree();
	~SceneMatchThree();

	void onChessTouched(const GEvent & touchEvent);

	void clearTouchedChessList();

	void gotScore(const int score);

	int getTotalScore() const;

	MatchThreeBoard * getBoard() const { return board.get(); }
	const std::vector<GEntity *> & getTouchedChessList() const { return touchedChessList; }

private:
	void onUpdate(const GEvent & event);
	void onQuitGameClicked();
	void restoreTouchedChessList();
	bool isTimeUp() const;

private:
	virtual void doOnEnter() override;
	virtual void doOnExit() override;

private:
	std::unique_ptr<GStateMachine> stateMachine;
	std::unique_ptr<MatchThreeBoard> board;
	std::unique_ptr<MatchThreeInfoView> infoView;
	std::vector<GEntity *> touchedChessList;

	GPoint previousTouchPosition;

	unsigned int roundStartMilliseconds;
};


} //namespace gincu


#endif
