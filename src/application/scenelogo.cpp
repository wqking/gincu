#include "scenelogo.h"
#include "scenemenu.h"
#include "matchthree/matchthreechess.h"
#include "matchthree/matchthreeconsts.h"
#include "framework/gameapplication.h"
#include "framework/scenemanager.h"
#include "framework/entity.h"
#include "framework/componentrender.h"
#include "framework/componenttransform.h"
#include "framework/componenttouchhandler.h"
#include "framework/componentanchor.h"
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
	GameColor textColor;
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
	const GameApplication * application = GameApplication::getInstance();

	const int itemCount = (int)logoItemList.size();
	const CoordType viewWidth = application->getViewSize().width;
	const CoordType viewHeight = application->getViewSize().height;
	const CoordType xSpace = 40;
	const CoordType ySize = xSpace;
	const CoordType startX = viewWidth / 2 - (itemCount -1) * xSpace / 2;
	const cpgf::GTweenNumber firstTweenDuration = 400;

	this->addEntity(
		(new Entity())
			->addComponent(createComponent<ComponentTransform>(GamePoint { 0, 0 }, 3.25f))
			->addComponent(createAndLoadImageComponent(backgroundImageName))
	);


	cpgf::GTimeline & timeline = cpgf::GTweenList::getInstance()->timeline();
	timeline.onComplete(cpgf::makeCallback(this, &SceneLogo::doExitLogo));

	CoordType x = startX - xSpace;
	cpgf::GTweenNumber delay = 0;
	for(int i = 0; i < itemCount; ++i) {
		x += xSpace;

		const LogoItem & item = logoItemList[i];

		if(item.text.empty()) {
			continue;
		}

		Entity * entity = this->addEntity(
			(new Entity())
				->addComponent(createComponent<ComponentTransform>(GamePoint { x, -ySize }, 1.0f ))
				->addComponent(createComponent<ComponentAnchor>(RenderAnchor_Center))
				->addComponent(createImageComponent(getChessResource(item.chessColor)))
			);
		ComponentTransform * transform = entity->getComponentByType<ComponentTransform>();
		timeline.setAt(delay,
			timeline.tween()
				.duration(firstTweenDuration)
				.ease(cpgf::QuadEase::easeOut())
				.target(cpgf::createAccessor(transform, &ComponentTransform::getPosition, &ComponentTransform::setPosition),   GamePoint{transform->getPosition().x, viewHeight / 2 + 100})
				.onComplete([=]() {
						entity->addComponent(createAndLoadTextComponent(item.text, item.textColor, largeFontSize));
					}
				)
		);
		timeline.setAt(delay + firstTweenDuration,
			timeline.tween()
				.duration(300)
				.ease(cpgf::QuadEase::easeOut())
				.target(cpgf::createAccessor(transform, &ComponentTransform::getPosition, &ComponentTransform::setPosition),   GamePoint{transform->getPosition().x, viewHeight / 2})
		);

		delay += 100;
	}

	if(this->showProgressBar) {
		const CoordType progressBarWidth = 600;
		const CoordType progressBarHeight = 20;
		const GamePoint startPosition { viewWidth / 2 - progressBarWidth / 2, viewHeight - progressBarHeight - 20 };

		Entity * progressBarEntity = this->addEntity(
			(new Entity())
				->addComponent(createComponent<ComponentTransform>(startPosition, 1.0f))
				->addComponent(createComponent<ComponentAnchor>(RenderAnchor_Hleft | RenderAnchor_Vcenter))
				->addComponent(createRectRenderComponent(0x770000aa, GameSize { 0.0f, progressBarHeight }))
			);
		Entity * chessEntity = this->addEntity(
			(new Entity())
				->addComponent(createComponent<ComponentTransform>(startPosition, 1.0f ))
				->addComponent(createComponent<ComponentAnchor>(RenderAnchor_Center))
				->addComponent(createImageComponent(getChessResource(ChessColor::normal3)))
		);

		RectRender & rectRender = progressBarEntity->getComponentByType<ComponentRectRender>()->getRender();
		ComponentTransform * transform = chessEntity->getComponentByType<ComponentTransform>();
		timeline.setAt(0,
			timeline.tween()
				.duration(timeline.getDuration())
				.ease(cpgf::LinearEase::easeIn())
				.target(cpgf::createAccessor(&rectRender, &RectRender::getSize, &RectRender::setSize), GameSize{progressBarWidth, rectRender.getSize().height} )
				.target(cpgf::createAccessor(transform, &ComponentTransform::getPosition, &ComponentTransform::setPosition),   GamePoint{startPosition.x + progressBarWidth, transform->getPosition().y})
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

void SceneLogo::onPressAnyKey(const TouchEvent & touchEvent)
{
	if(touchEvent.type == TouchEventType::eventPressed) {
		this->doExitLogo();
	}
}


G_AUTO_RUN_BEFORE_MAIN()
{
	MenuRegister::getInstance()->registerItem("about", 9999999, [](){
			GameApplication::getInstance()->getSceneManager()->switchScene(new SceneLogo(false));
		},
		0xffaaaaff);
}


} //namespace gincu
