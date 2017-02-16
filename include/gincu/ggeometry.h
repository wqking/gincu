#ifndef GGEOMETRY_H
#define GGEOMETRY_H

#include "gutil.h"

namespace gincu {

typedef float GCoord;

struct GVector2
{
	GCoord x;
	GCoord y;
};

inline GVector2 operator + (const GVector2 & a, const GVector2 & b)
{
	return GVector2{ a.x + b.x, a.y + b.y };
}

inline GVector2 operator - (const GVector2 & a, const GVector2 & b)
{
	return GVector2{ a.x - b.x, a.y - b.y };
}

inline GVector2 operator * (const GVector2 & a, const float b)
{
	return GVector2{ a.x * b, a.y * b };
}

inline bool operator == (const GVector2 & a, const GVector2 & b)
{
	return isEqual(a.x, b.x) && isEqual(a.y, b.y);
}

inline bool operator != (const GVector2 & a, const GVector2 & b)
{
	return !(a == b);
}

inline GVector2 operator - (const GVector2 & a)
{
	return GVector2{ -a.x, -a.y };
}

typedef GVector2 GPoint;
typedef GVector2 GScale;

struct GRect
{
	GCoord x;
	GCoord y;
	GCoord width;
	GCoord height;
};

struct GSize
{
	GCoord width;
	GCoord height;
};

inline GSize operator + (const GSize & a, const GSize & b)
{
	return GSize{ a.width + b.width, a.height + b.height };
}

inline GSize operator - (const GSize & a, const GSize & b)
{
	return GSize{ a.width - b.width, a.height - b.height };
}

inline GSize operator * (const GSize & a, const float b)
{
	return GSize{ a.width * b, a.height * b };
}

inline bool operator == (const GSize & a, const GSize & b)
{
	return isEqual(a.width, b.width) && isEqual(a.height, b.height);
}

inline bool operator != (const GSize & a, const GSize & b)
{
	return !(a == b);
}

inline GPoint getPosition(const GRect & rect)
{
	return { rect.x, rect.y };
}

inline GSize getSize(const GRect & rect)
{
	return { rect.width, rect.height };
}

inline bool operator == (const GRect & a, const GRect & b)
{
	return getPosition(a) == getPosition(b)
		&& getSize(a) == getSize(b)
	;
}

inline bool operator != (const GRect & a, const GRect & b)
{
	return !(a == b);
}

inline GRect createRect(const GPoint & position, const GSize & size)
{
	return GRect { position.x, position.y, size.width, size.height };
}

inline bool isInRect(const GPoint & point, const GRect & rect)
{
	return point.x >= rect.x && point.x <= rect.x + rect.width
		&& point.y >= rect.y && point.y <= rect.y + rect.height
	;
}

} //namespace gincu

#endif
