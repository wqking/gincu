#ifndef SCENEMENU_H
#define SCENEMENU_H

#include "gincu/gcolor.h"
#include "gincu/gscene.h"
#include "cpgf/gcallback.h"

#include <string>
#include <vector>

namespace gincu {

class SceneMenu : public GScene
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
	GColor backgroundColor;
};

class MenuRegister
{
public:
	static MenuRegister * getInstance();

public:
	void registerItem(const std::string & caption, const int order, const MenuCallback & callback, const GColor backgroundColor = 0xffeeee77);
	const std::vector<MenuItem> & getSortedItemList() const;

private:
	void sortItemList() const;

private:
	mutable std::vector<MenuItem> itemList;
};


} //namespace gincu

#endif
