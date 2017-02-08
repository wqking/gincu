#include "scenetestbed.h"
#include "scenemenu.h"
#include "uiutil.h"
#include "testbed.h"

#include "gincu/gapplication.h"
#include "gincu/gscenemanager.h"
#include "gincu/gentity.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/gcomponentanchor.h"

#include "cpgf/goutmain.h"

using namespace gincu;

void SceneTestBed::switchToScene()
{
	GApplication::getInstance()->getSceneManager()->switchScene("SceneTestBed", &sceneCreator<SceneTestBed>);
}

SceneTestBed::SceneTestBed()
	: testBed(new TestBed())
{
}

void SceneTestBed::doOnEnter()
{
	this->addEntity(createBackButton([=]() {
		GApplication::getInstance()->getSceneManager()->switchScene(new SceneMenu());
	}));

	const std::vector<TestCaseItem> & itemList = TestBedRegister::getInstance()->getSortedItemList();

	const GApplication * application = GApplication::getInstance();

	const int itemCount = (int)itemList.size();
	const GCoord viewWidth = application->getViewSize().width;
	const GCoord viewHeight = application->getViewSize().height;
	const GSize tileSize { 200, 60};
	const GCoord xSpace = 10;
	const GCoord ySpace = 10;
	const int fontSize = 24;
	const int rowCount = 7;

	const int actualRowCount = std::min(itemCount, rowCount);
	const int actualColumnCount = itemCount / rowCount + (itemCount % rowCount == 0 ? 0 : 1);

	const GCoord totalHeight = actualRowCount * tileSize.height + (actualRowCount - 1) * ySpace;
	const GCoord yStart = (viewHeight - totalHeight) / 2;
	const GCoord totalWidth = actualColumnCount * tileSize.width + (actualColumnCount - 1) * xSpace;
	const GCoord xStart = (viewWidth - totalWidth) / 2;

	for(int i = 0; i < itemCount; ++i) {
		const auto item = itemList[i];
		const int row = i % rowCount;
		const int column = i / rowCount;
		this->addEntity(
			(new GEntity())
			->addComponent(createComponent<GComponentTransform>())
			->addComponent(createComponent<GComponentLocalTransform>(GPoint { xStart + (tileSize.width + xSpace) * column, yStart + (tileSize.height + ySpace) * row }))
			->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
			->addComponent(createComponent<GComponentContainerRender>()
				->add(createRectRenderComponent(0xffeeee77, tileSize))
				->add(createAndLoadTextComponent(item.caption, colorBlue, fontSize))
			)
			->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch([=](const GTouchEvent & touchEvent) {
			if(touchEvent.type == GTouchEventType::eventPressed) {
				this->testBed->executeTestCase(item.creator());
			}
		}))
		);
	}
}

void SceneTestBed::doOnExit()
{
}

G_AUTO_RUN_BEFORE_MAIN()
{
	MenuRegister::getInstance()->registerItem("test bed", 2, [](){
			SceneTestBed::switchToScene();
		},
		0xffeeee77);
}

