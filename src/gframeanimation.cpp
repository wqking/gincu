#include "gincu/gframeanimation.h"
#include "gincu/gapplication.h"
#include "gincu/gatlas.h"
#include "gincu/glog.h"

#include "cpgf/accessor/gaccessor.h"

#include <map>
#include <vector>

namespace gincu {

GFrameAnimationSetData::GFrameAnimationSetData()
{
}

GFrameAnimationSetData::~GFrameAnimationSetData()
{
}

void GFrameAnimationSetData::append(const std::string & name, GFrameAnimationData && animationData)
{
	this->animationDataList.push_back({ name, animationData });
	AnimationDataItem * item = &this->animationDataList.back();
	this->nameMap.insert(std::make_pair(std::reference_wrapper<const std::string>(item->name), item));
}

const GFrameAnimationData * GFrameAnimationSetData::getAnimationData(const std::string & name) const
{
	auto it = this->nameMap.find(name);
	if(it == this->nameMap.end()) {
		G_LOG_ERROR("Can't find animation name %s", name.c_str());
		return nullptr;
	}
	else {
		return &it->second->data;
	}
}


namespace {

void extractAnimationNameAndIndex(const std::string & resourceName, std::string & animationName, int & frameOrder)
{
	frameOrder = -1;
	if(resourceName.empty()) {
		animationName = "";
		return;
	}

	const int size = (int)resourceName.size();
	int digitEnd = size - 1;
	int digitStart = digitEnd;
	while(digitStart > 0 && isdigit(resourceName[digitStart])) {
		--digitStart;
	}
	++digitStart;

	frameOrder = 0;
	for(int i = digitStart; i <= digitEnd; ++i) {
		frameOrder = frameOrder * 10 + (resourceName[i] - '0');
	}

	int nameEnd = digitStart;
	for(;;) {
		--nameEnd;

		if(nameEnd <= 0) break;

		const char c = resourceName[nameEnd];
		if(isdigit(c)) continue;
		if(c == '-' || c == '_') continue;

		break;
	}

	animationName = resourceName.substr(0, nameEnd);
}

} //unnamed namespace

void buildFrameAnimationDataFromAtlas(GFrameAnimationSetData * data, const GAtlas & atlas, const int millsecondsBetweenFrame)
{
	struct Item {
		int frameOrder;
		int frameIndex;
	};

	std::map<std::string, std::vector<Item> > animationMap;

	auto spriteNameList = atlas.getNameList();

	for(const std::string & name : spriteNameList) {
		std::string animationName;
		int frameOrder;

		extractAnimationNameAndIndex(name, animationName, frameOrder);

		if(frameOrder < 0 || animationName.empty()) {
			continue;
		}

		animationMap[animationName].push_back({ frameOrder, atlas.getIndex(name) });
	}

	auto compare = [](const Item & a, const Item & b) { return a.frameOrder < b.frameOrder; };

	for(auto itemPair : animationMap) {
		std::sort(itemPair.second.begin(), itemPair.second.end(), compare);
		std::vector<int> indexList(itemPair.second.size());
		for(std::size_t i = 0; i < indexList.size(); ++i) {
			indexList[i] = itemPair.second[i].frameIndex;
		}
		const int duration = indexList.size() * millsecondsBetweenFrame;
		data->append(itemPair.first, GFrameAnimationData(std::move(indexList), duration));
	}
}


} //namespace gincu

