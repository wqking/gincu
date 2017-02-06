#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <sstream>
#include <cmath>

namespace gincu {

template <typename T, typename A, typename B>
inline bool isWithin(const T value, const A a, const B b)
{
	return value >= a && value < b;
}

template <typename T>
std::string toString(const T & value)
{
	std::ostringstream stream;
	stream << value;
	return stream.str();
}

inline bool isEqual(const int a, const int b)
{
	return a == b;
}

inline bool isEqual(const unsigned int a, const unsigned int b)
{
	return a == b;
}

inline bool isEqual(const long long a, const long long b)
{
	return a == b;
}

inline bool isEqual(const double a, const double b)
{
	return fabs(a - b) <= std::numeric_limits<double>::epsilon();
}

inline bool isEqual(const float a, const float b)
{
	return fabs(a - b) <= std::numeric_limits<float>::epsilon();
}

inline float degreeToRadian(const float degree)
{
	return degree * 3.141592654f / 180.0f;
}

int getRand();
int getRand(const int min, const int max);
int getRand(const int max);

// implemented in engineutil.cpp
void sleepMilliseconds(const unsigned int milliseconds);

// implemented in engineutil.cpp
unsigned int getMilliseconds();


} //namespace gincu

#endif
