#include "gincu/gdevicecontext.h"

namespace gincu {

namespace {

GDeviceContext * instance = nullptr;

} //unnamed namespace

GDeviceContext * GDeviceContext::getInstance()
{
	return instance;
}

GDeviceContext::GDeviceContext()
{
	instance = this;
}

GDeviceContext::~GDeviceContext()
{
}


GDeviceContextRegister * GDeviceContextRegister::getInstance()
{
	static GDeviceContextRegister instance;
	return &instance;
}


} //namespace gincu

