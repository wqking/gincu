#include "scenelogo.h"
#include "scenemenu.h"
#include "matchthree/matchthreechess.h"
#include "matchthree/matchthreeconsts.h"
#include "gincu/gapplication.h"
#include "gincu/gscenemanager.h"
#include "gincu/gentity.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/gcomponentanchor.h"
#include "gincu/gcomponentcamera.h"
#include "gincu/gevent.h"
#include "gincu/grenderanchor.h"

#include "cpgf/tween/gtimeline.h"
#include "cpgf/tween/gtweenlist.h"
#include "cpgf/tween/easing/quad.h"
#include "cpgf/tween/easing/linear.h"
#include "cpgf/accessor/gaccessor.h"
#include "cpgf/goutmain.h"

#include <vector>
#include <string>

namespace gincu {

namespace {

struct LogoItem
{
	ChessColor chessColor;
	std::string text;
	GColor textColor;
};

const std::vector<LogoItem> logoItemList {
	{ ChessColor::normal0, "G", colorBlue },
	{ ChessColor::normal1, "I", colorGreen },
	{ ChessColor::normal2, "N", colorPurple },
	{ ChessColor::normal3, "C", colorRed },
	{ ChessColor::normal4, "U", 0xffdddd00 },
	{ ChessColor::normal0, "", 0 },
	{ ChessColor::normal4, "G", 0xffdddd00 },
	{ ChessColor::normal3, "A", colorBlue },
	{ ChessColor::normal2, "M", 0xff00dddd },
	{ ChessColor::normal1, "E", 0xffdd00dd },
	{ ChessColor::normal1, "S", colorPurple },
};

}


SceneLogo::SceneLogo(const bool showProgressBar)
	: showProgressBar(showProgressBar)
{
}

SceneLogo::~SceneLogo()
{
}

void SceneLogo::doOnEnter()
{
	const int itemCount = (int)logoItemList.size();
	const GCoord viewWidth = this->getPrimaryCamera()->getWorldSize().width;
	const GCoord viewHeight = this->getPrimaryCamera()->getWorldSize().height;
	const GCoord xSpace = 40;
	const GCoord ySize = xSpace;
	const GCoord startX = viewWidth / 2 - (itemCount -1) * xSpace / 2;
	const cpgf::GTweenNumber firstTweenDuration = 400;

	this->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint { 0, 0 }, GScale { 3.25f, 3.25f }))
			->addComponent(createAndLoadImageComponent(backgroundImageName))
	);


	cpgf::GTimeline & timeline = getTweenListFromScene()->timeline();
	timeline.onComplete(cpgf::makeCallback(this, &SceneLogo::doExitLogo));

	GCoord x = startX - xSpace;
	cpgf::GTweenNumber delay = 0;
	for(int i = 0; i < itemCount; ++i) {
		x += xSpace;

		const LogoItem & item = logoItemList[i];

		if(item.text.empty()) {
			continue;
		}

		GEntity * entity = this->addEntity(
			(new GEntity())
				->addComponent(createComponent<GComponentTransform>(GPoint { x, -ySize } ))
				->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
				->addComponent(createChessRender(item.chessColor))
			);
		GComponentTransform * transform = entity->getComponentByType<GComponentTransform>();
		timeline.setAt(delay,
			timeline.tween()
				.duration(firstTweenDuration)
				.ease(cpgf::QuadEase::easeOut())
				.target(cpgf::createAccessor(transform, &GComponentTransform::getPosition, &GComponentTransform::setPosition),   GPoint{transform->getPosition().x, viewHeight / 2 + 100})
				.onComplete([=]() {
						entity->addComponent(createAndLoadTextComponent(item.text, item.textColor, largeFontSize));
					}
				)
		);
		timeline.setAt(delay + firstTweenDuration,
			timeline.tween()
				.duration(300)
				.ease(cpgf::QuadEase::easeOut())
				.target(cpgf::createAccessor(transform, &GComponentTransform::getPosition, &GComponentTransform::setPosition),   GPoint{transform->getPosition().x, viewHeight / 2})
		);

		delay += 100;
	}

	if(this->showProgressBar) {
		const GCoord progressBarWidth = 600;
		const GCoord progressBarHeight = 20;
		const GPoint startPosition { viewWidth / 2 - progressBarWidth / 2, viewHeight - progressBarHeight - 20 };

		GEntity * progressBarEntity = this->addEntity(
			(new GEntity())
				->addComponent(createComponent<GComponentTransform>(startPosition))
				->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::hLeft | GRenderAnchor::vCenter))
				->addComponent(createRectRenderComponent(0x770000aa, GSize { 0.0f, progressBarHeight }))
			);
		GEntity * chessEntity = this->addEntity(
			(new GEntity())
				->addComponent(createComponent<GComponentTransform>(startPosition ))
				->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
				->addComponent(createChessRender(ChessColor::normal3))
		);

		GRectRender & rectRender = progressBarEntity->getComponentByType<GComponentRectRender>()->getRender();
		GComponentTransform * transform = chessEntity->getComponentByType<GComponentTransform>();
		timeline.setAt(0,
			timeline.tween()
				.duration(timeline.getDuration())
				.ease(cpgf::LinearEase::easeIn())
				.target(cpgf::createAccessor(&rectRender, &GRectRender::getSize, &GRectRender::setSize), GSize{progressBarWidth, rectRender.getSize().height} )
				.target(cpgf::createAccessor(transform, &GComponentTransform::getPosition, &GComponentTransform::setPosition),   GPoint{startPosition.x + progressBarWidth, transform->getPosition().y})
		);
	}

	timeline.append(timeline.tween().duration(1000));
}

void SceneLogo::doOnExit()
{
	cpgf::GTweenList::getInstance()->clear();
}

void SceneLogo::doExitLogo()
{
	SceneMenu::returnToMainMenu();
}

void SceneLogo::onPressAnyKey(const GEvent & touchEvent)
{
	if(touchEvent.type == GEventType::touchPressed) {
		this->doExitLogo();
	}
}


G_AUTO_RUN_BEFORE_MAIN()
{
	MenuRegister::getInstance()->registerItem("about", 9999999, [](){
			GApplication::getInstance()->getSceneManager()->switchScene(new SceneLogo(false));
		},
		0xffaaaaff);
}


} //namespace gincu
