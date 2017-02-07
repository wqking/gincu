#include "gincu/gerrorhandler.h"
#include "gincu/glog.h"

#include <exception>

namespace gincu {

void handleFatal(const std::string & message)
{
	G_LOG_FATAL(message.c_str());
	std::terminate();
}


} //namespace gincu
