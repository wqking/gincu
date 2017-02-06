#ifndef MATCHTHREEINFOVIEW_H
#define MATCHTHREEINFOVIEW_H

#include "cpgf/tween/gtween.h"
#include "cpgf/tween/gtimeline.h"

namespace gincu {

class SceneMatchThree;
class Entity;

class MatchThreeInfoView
{
public:
	explicit MatchThreeInfoView(SceneMatchThree * scene);
	~MatchThreeInfoView();

	void addScore(const int score);
	void setRemainingSeconds(int seconds);

	int getTotalScore() const { return totalScore; }
	int getRemainingSeconds() const { return remainingSeconds; }

private:
	void applyScoreDisplay();
	void onScoreTweenFinish();

private:
	SceneMatchThree * scene;
	Entity * scoreEntity;
	Entity * scoreIncrementEntity;
	Entity * timerEntity;

	cpgf::GTween * scoreTween;
	cpgf::GTimeline * timerTimeLine;

	int totalScore;
	int remainingSeconds;
};


} //namespace gincu

#endif
