#ifndef GTRANSITION_H
#define GTRANSITION_H

#include "cpgf/tween/gtween.h"
#include "cpgf/gcallbacklist.h"

namespace gincu {

class GScene;

class GTransition
{
public:
	GTransition();
	virtual ~GTransition();
	
	void transite(GScene * fromScene, GScene * toScene);
	void cancel();

	void addOnComplete(const cpgf::GCallback<void ()> & onComplete);

	cpgf::GTween & getTween() const;
	
protected:
	void finish();
	
private:
	virtual void doTransite(GScene * fromScene, GScene * toScene);
	
private:
	mutable cpgf::GTween * tween;
	cpgf::GCallbackList<void ()> onCompleteList;
};


} //namespace gincu


#endif

