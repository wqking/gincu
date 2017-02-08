#include "gincu/gframeanimation.h"
#include "gincu/gapplication.h"
#include "gincu/gspritesheet.h"
#include "gincu/glog.h"

#include "cpgf/accessor/gaccessor.h"

#include <map>
#include <vector>

namespace gincu {

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


GTweenedFrameAnimation::GTweenedFrameAnimation()
	: GTweenedFrameAnimation(std::shared_ptr<GFrameAnimationSetData>())
{
}

GTweenedFrameAnimation::GTweenedFrameAnimation(const std::shared_ptr<GFrameAnimationSetData> & data)
	:
		data(data),
		currentAnimation(nullptr),
		tween(std::make_shared<cpgf::GTween>()),
		needInitialize(true)
{
	this->tween->useFrames(true);

	if(this->data && this->data->getAnimationCount() > 0) {
		this->setAnimation(this->data->getAnimationNameAt(0));
	}
}

GTweenedFrameAnimation::~GTweenedFrameAnimation()
{
}

void GTweenedFrameAnimation::update()
{
	if(this->needInitialize) {
		this->needInitialize = false;
		this->tween->target(cpgf::createAccessor(this, 0.0f, &GTweenedFrameAnimation::doSetRatio), 0.0f, 1.0f);
	}

	this->tween->tick((cpgf::GTweenNumber)GApplication::getInstance()->getFrameMilliseconds());
}

void GTweenedFrameAnimation::setAnimation(const std::string & name)
{
	this->currentAnimation = this->data->getAnimationData(name);
	if(this->currentAnimation != nullptr) {
		this->tween->duration((cpgf::GTweenNumber)this->currentAnimation->getFrameIndexList().size());
		this->tween->restart();
	}
}

void GTweenedFrameAnimation::doSetRatio(const float ratio)
{
	if(this->currentAnimation != nullptr) {
		auto frameIndexList = this->currentAnimation->getFrameIndexList();
		const int frameCount = (int)frameIndexList.size();
		const int index = (int)((float)frameCount * ratio);
		if(index < frameCount && this->updater) {
			this->updater(index);
		}
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

void buildFrameAnimationDataFromSpriteSheet(GFrameAnimationSetData * data, const GSpriteSheet & spriteSheet)
{
	struct Item {
		int frameOrder;
		int frameIndex;
	};

	std::map<std::string, std::vector<Item> > animationMap;

	auto spriteNameList = spriteSheet.getNameList();

	for(const std::string & name : spriteNameList) {
		std::string animationName;
		int frameOrder;

		extractAnimationNameAndIndex(name, animationName, frameOrder);

		if(frameOrder < 0 || animationName.empty()) {
			continue;
		}

		animationMap[animationName].push_back({ frameOrder, spriteSheet.getIndex(name) });
	}

	auto compare = [](const Item & a, const Item & b) { return a.frameOrder < b.frameOrder; };

	for(auto itemPair : animationMap) {
		std::sort(itemPair.second.begin(), itemPair.second.end(), compare);
		std::vector<int> indexList(itemPair.second.size());
		for(std::size_t i = 0; i < indexList.size(); ++i) {
			indexList[i] = itemPair.second[i].frameIndex;
		}
		data->append(itemPair.first, GFrameAnimationData(std::move(indexList)));
	}
}


} //namespace gincu

