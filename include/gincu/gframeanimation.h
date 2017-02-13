#ifndef GFRAMEANIMATION_H
#define GFRAMEANIMATION_H

#include "gincu/gutil.h"

#include "cpgf/tween/gtween.h"
#include "cpgf/gcallback.h"

#include <vector>
#include <deque>
#include <map>
#include <string>
#include <memory>
#include <functional>

namespace gincu {

class GFrameAnimationData
{
public:
	GFrameAnimationData() {}
	explicit GFrameAnimationData(std::vector<int> && frameIndexList) : frameIndexList(frameIndexList) {}

	const std::vector<int> & getFrameIndexList() const { return this->frameIndexList; }

private:
	std::vector<int> frameIndexList;
};


class GFrameAnimationSetData
{
private:
	struct AnimationDataItem
	{
		std::string name;
		GFrameAnimationData data;
	};

public:
	void append(const std::string & name, GFrameAnimationData && animationData);

	const GFrameAnimationData * getAnimationData(const std::string & name) const;

	int getAnimationCount() const { return (int)this->animationDataList.size(); }
	const std::string & getAnimationNameAt(const int index) const { return this->animationDataList[index].name; }
	const GFrameAnimationData * getAnimationDataAt(const int index) const { return &this->animationDataList[index].data; }

private:
	// use deque instead of vector because we need reference to elements not invalidate after push_back
	// C++ standard guarantees that:
	// An insert at either end of the deque invalidates all the iterators to the deque, but has no effect on the validity of references to elements of the deque.
	std::deque<AnimationDataItem> animationDataList;
	std::map<std::reference_wrapper<const std::string>, AnimationDataItem *, ReferenceWrapperLessCompare<std::reference_wrapper<const std::string> > > nameMap;
};


class GTweenedFrameAnimation
{
public:
	typedef cpgf::GCallback<void (int)> AnimationUpdater;

public:
	GTweenedFrameAnimation();
	explicit GTweenedFrameAnimation(const std::shared_ptr<GFrameAnimationSetData> & data);
	~GTweenedFrameAnimation();

	void update();

	void setAnimation(const std::string & name);

	cpgf::GTween & getTween() { return *this->tween.get(); }
	
	void setUpdater(const AnimationUpdater & updater) { this->updater = updater; }

private:
	void doSetRatio(const float ratio);

private:
	std::shared_ptr<GFrameAnimationSetData> data;
	const GFrameAnimationData * currentAnimation;
	std::shared_ptr<cpgf::GTween> tween;
	AnimationUpdater updater;
	bool needInitialize;
};

class GAtlas;

void buildFrameAnimationDataFromAtlas(GFrameAnimationSetData * data, const GAtlas & atlas);


} //namespace gincu


#endif
