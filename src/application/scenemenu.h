#ifndef SCENEMENU_H
#define SCENEMENU_H

#include "engine/gamecolor.h"
#include "framework/scene.h"
#include "cpgf/gcallback.h"

#include <string>
#include <vector>

namespace gincu {

struct TouchEvent;

class SceneMenu : public Scene
{
public:
	static void returnToMainMenu();

private:
	virtual void doOnEnter() override;
	virtual void doOnExit() override;
};


typedef cpgf::GCallback<void ()> MenuCallback;

struct MenuItem
{
	std::string caption;
	int order;
	MenuCallback callback;
	GameColor backgroundColor;
};

class MenuRegister
{
public:
	static MenuRegister * getInstance();

public:
	void registerItem(const std::string & caption, const int order, const MenuCallback & callback, const GameColor backgroundColor = 0xffeeee77);
	const std::vector<MenuItem> & getSortedItemList() const;

private:
	void sortItemList() const;

private:
	mutable std::vector<MenuItem> itemList;
};


} //namespace gincu

#endif
