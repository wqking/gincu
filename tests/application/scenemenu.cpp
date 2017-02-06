#include "scenemenu.h"
#include "scenelogo.h"
#include "matchthree/scenematchthree.h"
#include "constants.h"
#include "gincu/gapplication.h"
#include "gincu/gscenemanager.h"
#include "gincu/gentity.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/gcomponentanchor.h"

#include <algorithm>

namespace gincu {

void SceneMenu::returnToMainMenu()
{
	GameApplication::getInstance()->getSceneManager()->switchScene(new SceneMenu());
}

void SceneMenu::doOnEnter()
{
	const GameApplication * application = GameApplication::getInstance();

	const CoordType viewWidth = application->getViewSize().width;
	const CoordType viewHeight = application->getViewSize().height;
	const GameSize tileSize { 400, 80};
	const CoordType yDistance = 40;

	this->addEntity(
		(new Entity())
		->addComponent(createComponent<ComponentTransform>(GamePoint { -700, -230 }, GameScale { 2.2f, 2.2f }))
			->addComponent(createAndLoadImageComponent(menuBackgroundImageName))
	);

	auto itemList = MenuRegister::getInstance()->getSortedItemList();
	const int itemCount = (int)itemList.size();
	const CoordType totalHeight = itemCount * tileSize.height + (itemCount - 1) * itemCount;
	const CoordType yStart = (viewHeight - totalHeight) / 2;
	const CoordType x = viewWidth / 2;

	for(int i = 0; i < itemCount; ++i) {
		const auto item = itemList[i];
		this->addEntity(
			(new Entity())
				->addComponent(createComponent<ComponentTransform>())
				->addComponent(createComponent<ComponentLocalTransform>(GamePoint { x, yStart + (tileSize.height + yDistance) * i }))
				->addComponent(createComponent<ComponentAnchor>(RenderAnchor::center))
				->addComponent(createComponent<ComponentContainerRender>()
					->add(createRectRenderComponent(item.backgroundColor, tileSize))
					->add(createAndLoadTextComponent(item.caption, colorBlue, menuFontSize))
				)
				->addComponent(createComponent<ComponentRendererTouchHandler>()->addOnTouch([=](const TouchEvent & touchEvent) {
					if(touchEvent.type == TouchEventType::eventPressed) {
						item.callback();
					}
				}))
		);
	}
}

void SceneMenu::doOnExit()
{
}


MenuRegister * MenuRegister::getInstance()
{
	static MenuRegister instance;

	return &instance;
}

void MenuRegister::registerItem(const std::string & caption, const int order, const MenuCallback & callback, const GameColor backgroundColor)
{
	this->itemList.push_back({
		caption,
		order,
		callback,
		backgroundColor
	});
}

const std::vector<MenuItem> & MenuRegister::getSortedItemList() const
{
	this->sortItemList();
	return this->itemList;
}

void MenuRegister::sortItemList() const
{
	std::sort(this->itemList.begin(), this->itemList.end(), [](const MenuItem & a, const MenuItem & b) { return a.order < b.order; });
}


} //namespace gincu
