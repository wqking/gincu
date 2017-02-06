#ifndef GGEOMETRY_H
#define GGEOMETRY_H

namespace gincu {

typedef float CoordType;

struct GameVector2
{
	CoordType x;
	CoordType y;
};

inline GameVector2 operator + (const GameVector2 & a, const GameVector2 & b)
{
	return GameVector2{ a.x + b.x, a.y + b.y };
}

inline GameVector2 operator - (const GameVector2 & a, const GameVector2 & b)
{
	return GameVector2{ a.x - b.x, a.y - b.y };
}

inline GameVector2 operator * (const GameVector2 & a, const float b)
{
	return GameVector2{ a.x * b, a.y * b };
}

inline bool operator == (const GameVector2 & a, const GameVector2 & b)
{
	return a.x == b.x && a.y == b.y;
}

inline bool operator != (const GameVector2 & a, const GameVector2 & b)
{
	return !(a == b);
}

inline GameVector2 operator - (const GameVector2 & a)
{
	return GameVector2{ -a.x, -a.y };
}

struct GameRect
{
	CoordType x;
	CoordType y;
	CoordType width;
	CoordType height;
};

struct GameSize
{
	CoordType width;
	CoordType height;
};

inline GameSize operator + (const GameSize & a, const GameSize & b)
{
	return GameSize{ a.width + b.width, a.height + b.height };
}

inline GameSize operator - (const GameSize & a, const GameSize & b)
{
	return GameSize{ a.width - b.width, a.height - b.height };
}

inline GameSize operator * (const GameSize & a, const float b)
{
	return GameSize{ a.width * b, a.height * b };
}

typedef GameVector2 GamePoint;
typedef GameVector2 GameScale;

struct RowColumn
{
	int row;
	int column;
};


} //namespace gincu

#endif
