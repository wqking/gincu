#include "matchthree/matchthreeinfoview.h"
#include "matchthree/scenematchthree.h"
#include "matchthree/matchthreeconsts.h"
#include "gincu/gentity.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponentanchor.h"
#include "gincu/gutil.h"
#include "cpgf/tween/gtweenlist.h"
#include "cpgf/tween/easing/quad.h"
#include "cpgf/accessor/gaccessor.h"

namespace gincu {

MatchThreeInfoView::MatchThreeInfoView(SceneMatchThree * scene)
	:
		scene(scene),
		scoreEntity(nullptr),
		scoreIncrementEntity(nullptr),
		timerEntity(nullptr),
		scoreTween(nullptr),
		timerTimeLine(nullptr),
		totalScore(0)
{
	this->scoreEntity = this->scene->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint { 115, 180 }))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
		->addComponent(createAndLoadTextComponent("0", colorWhite, normalFontSize))
	);
	this->scoreIncrementEntity = this->scene->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint(), GScale { 0.8f, 0.8f }, false))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
		->addComponent(createAndLoadTextComponent("0", colorGreen, normalFontSize))
	);
	this->timerEntity = this->scene->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint { 115, 220 }))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
		->addComponent(createAndLoadTextComponent("0", colorBlack, normalFontSize))
		);

	this->applyScoreDisplay();
}

MatchThreeInfoView::~MatchThreeInfoView()
{

}

void MatchThreeInfoView::setRemainingSeconds(int seconds)
{
	if(seconds < 0) {
		seconds = 0;
	}
	if(seconds == this->remainingSeconds) {
		return;
	}
	this->remainingSeconds = seconds;

	const bool shouldWarn = (this->remainingSeconds <= 10);
	this->timerEntity->getComponentByType<GComponentTextRender >()->getRender().setTextAndColor(
		toString(this->remainingSeconds), (shouldWarn ? colorRed : colorBlack)
	);

	if(this->timerTimeLine != nullptr) {
		cpgf::GTweenList::getInstance()->remove(*this->timerTimeLine);
	}

	GComponentTransform * transform = this->timerEntity->getComponentByType<GComponentTransform>();
	transform->setScale(GScale { 1.0f, 1.0f });

	if(shouldWarn && this->remainingSeconds > 0) {
		this->timerTimeLine = &cpgf::GTweenList::getInstance()->timeline();
		this->timerTimeLine->append(
			this->timerTimeLine->tween()
				.duration(300.0f)
		);
		this->timerTimeLine->append(
			timerTimeLine->tween()
				.duration(300.0f)
				.ease(cpgf::QuadEase::easeIn())
				.target(cpgf::createAccessor(transform, &GComponentTransform::getScale, &GComponentTransform::setScale), GScale { 2.0f, 2.0f })
		);
		this->timerTimeLine->append(
			this->timerTimeLine->tween()
			.duration(100.0f)
			);
		this->timerTimeLine->append(
			this->timerTimeLine->tween()
				.duration(300.0f)
				.ease(cpgf::QuadEase::easeOut())
				.target(cpgf::createAccessor(transform, &GComponentTransform::getScale, &GComponentTransform::setScale), GScale { 1.0f, 1.0f })
		);
	}
}

void MatchThreeInfoView::addScore(const int score)
{
	if(this->scoreTween != nullptr) {
		this->applyScoreDisplay();
	}

	this->totalScore += score;
	
	const GPoint targetPosition = scoreEntity->getComponentByType<GComponentTransform>()->getPosition();

	this->scoreIncrementEntity->getComponentByType<GComponentTextRender >()->getRender().setText("+" + toString(score));
	GComponentTransform * incrementTransform = this->scoreIncrementEntity->getComponentByType<GComponentTransform>();
	incrementTransform->setVisible(true);
	incrementTransform->setPosition(GPoint { targetPosition.x + 50, targetPosition.y - 50 });
	this->scoreTween = &cpgf::GTweenList::getInstance()->tween()
		.duration(500.0f)
		.ease(cpgf::QuadEase::easeIn())
		.onComplete(cpgf::makeCallback(this, &MatchThreeInfoView::onScoreTweenFinish))
		.target(cpgf::createAccessor(incrementTransform, &GComponentTransform::getPosition, &GComponentTransform::setPosition), targetPosition)
	;
}

void MatchThreeInfoView::applyScoreDisplay()
{
	if(this->scoreTween != nullptr) {
		cpgf::GTween * tempTween = this->scoreTween;
		scoreTween = nullptr;
		cpgf::GTweenList::getInstance()->remove(*tempTween);
	}
	this->scoreIncrementEntity->getComponentByType<GComponentTransform>()->setVisible(false);
	this->scoreEntity->getComponentByType<GComponentTextRender >()->getRender().setText(toString(totalScore));
}

void MatchThreeInfoView::onScoreTweenFinish()
{
	this->scoreTween = nullptr;
	this->applyScoreDisplay();
}


} //namespace gincu
