#ifndef GCOMPONENTLOCALTRANSFORM_H
#define GCOMPONENTLOCALTRANSFORM_H

#include "gincu/ecs/gcomponenttransformbase.h"

#include <vector>

namespace gincu {

class GComponentLocalTransform : public GComponentTransformBase<GComponentLocalTransform>
{
private:
	typedef GComponentTransformBase<GComponentLocalTransform> super;

public:
	inline static constexpr GComponentType getComponentType() {
		return GComponentType::localTransform;
	}
	
public:
	GComponentLocalTransform();
	explicit GComponentLocalTransform(const GPoint & position, const GScale & scale = {1.0f, 1.0f}, const bool visible = true);
 	~GComponentLocalTransform();
	
	GComponentLocalTransform * setParent(GComponentLocalTransform * parent);
	GComponentLocalTransform * getParent() const { return this->parent; }
	
	void applyGlobal();
	
	int getChildCount() const { return (int)this->children.size(); }
	GComponentLocalTransform * getChildAt(const int index) const { return this->children[index]; }
	const std::vector<GComponentLocalTransform *> & getSortedChildren() const;

private:
	void addChild(GComponentLocalTransform * child);
	void removeChild(GComponentLocalTransform * child);

private:
	virtual void doAfterZOrderChanged() override;

private:
	GComponentLocalTransform * parent;
	mutable std::vector<GComponentLocalTransform *> children;
	mutable bool needSortChildren;
};


} //namespace gincu

#endif
