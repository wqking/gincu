#include "gincu/gobjectfactory.h"
#include "gincu/gerrorhandler.h"

namespace gincu {

void GObjectFactoryBase::raiseCantFindError(const std::string & name) const
{
	handleFatal("Object factory: can't find " + name);
}

} //namespace gincu
