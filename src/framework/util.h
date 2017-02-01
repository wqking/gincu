#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <sstream>

namespace gincu {

template <typename T, typename A, typename B>
inline bool isWithin(const T value, const A a, const B b)
{
	return value >= a && value < b;
}

int getRand();
int getRand(const int min, const int max);
int getRand(const int max);

unsigned int getMilliseconds();

template <typename T>
std::string toString(const T & value)
{
	std::ostringstream stream;
	stream << value;
	return stream.str();
}


} //namespace gincu

#endif
