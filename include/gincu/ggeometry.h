#ifndef GGEOMETRY_H
#define GGEOMETRY_H

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
	return a.x == b.x && a.y == b.y;
}

inline bool operator != (const GVector2 & a, const GVector2 & b)
{
	return !(a == b);
}

inline GVector2 operator - (const GVector2 & a)
{
	return GVector2{ -a.x, -a.y };
}

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

typedef GVector2 GPoint;
typedef GVector2 GScale;

struct RowColumn
{
	int row;
	int column;
};


} //namespace gincu

#endif
