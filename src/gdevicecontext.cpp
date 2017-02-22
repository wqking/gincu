#include "gincu/gdevicecontext.h"

namespace gincu {

GDeviceContext::~GDeviceContext()
{
}


GDeviceContextRegister * GDeviceContextRegister::getInstance()
{
	static GDeviceContextRegister instance;
	return &instance;
}


} //namespace gincu

