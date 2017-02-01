#ifndef GEOMETRY_H
#define GEOMETRY_H

namespace gincu {

typedef float CoordType;

struct GamePoint
{
	CoordType x;
	CoordType y;
};

inline GamePoint operator + (const GamePoint & a, const GamePoint & b)
{
	return GamePoint{ a.x + b.x, a.y + b.y };
}

inline GamePoint operator - (const GamePoint & a, const GamePoint & b)
{
	return GamePoint{ a.x - b.x, a.y - b.y };
}

inline GamePoint operator * (const GamePoint & a, const float b)
{
	return GamePoint{ a.x * b, a.y * b };
}

inline bool operator == (const GamePoint & a, const GamePoint & b)
{
	return a.x == b.x && a.y == b.y;
}

inline bool operator != (const GamePoint & a, const GamePoint & b)
{
	return !(a == b);
}

inline GamePoint operator - (const GamePoint & a)
{
	return GamePoint{ -a.x, -a.y };
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

struct GameScale
{
	float x;
	float y;
};


struct RowColumn
{
	int row;
	int column;
};


} //namespace gincu

#endif
