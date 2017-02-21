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
	GFrameAnimationData()
		: frameIndexList(), durationMilliseconds(0)
	{}

	GFrameAnimationData(std::vector<int> && frameIndexList, const int durationMilliseconds)
		: frameIndexList(frameIndexList), durationMilliseconds(durationMilliseconds)
	{}

	const std::vector<int> & getFrameIndexList() const { return this->frameIndexList; }
	int getDurationMilliseconds() const { return this->durationMilliseconds; }

private:
	std::vector<int> frameIndexList;
	int durationMilliseconds;
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


class GAtlas;

void buildFrameAnimationDataFromAtlas(GFrameAnimationSetData * data, const GAtlas & atlas, const int millsecondsBetweenFrame = 30);


} //namespace gincu


#endif
