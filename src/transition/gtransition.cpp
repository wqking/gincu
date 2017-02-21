#include "gincu/transition/gtransition.h"

#include "cpgf/tween/gtweenlist.h"

namespace gincu {

GTransition::GTransition()
	: tween(nullptr)
{
}

GTransition::~GTransition()
{
	if(this->tween != nullptr) {
		cpgf::GTweenList::getInstance()->remove(*this->tween);
	}
}

cpgf::GTween & GTransition::getTween() const
{
	if(this->tween == nullptr) {
		this->tween = &cpgf::GTweenList::getInstance()->tween();
		this->tween->onDestroy([=](){ this->tween = nullptr; });
	}
	
	return *this->tween;
}

void GTransition::transite(GScene * fromScene, GScene * toScene)
{
	this->doTransite(fromScene, toScene);
}

void GTransition::addOnComplete(const cpgf::GCallback<void ()> & onComplete)
{
	this->onCompleteList.add(onComplete);
}

void GTransition::cancel()
{
	this->doFinalize();

	delete this;
}

void GTransition::finish()
{
	this->tween = nullptr;

	this->doFinalize();

	this->onCompleteList();

	delete this;
}

void GTransition::doFinalize()
{
}

void GTransition::doTransite(GScene * /*fromScene*/, GScene * /*toScene*/)
{
}


} //namespace gincu
