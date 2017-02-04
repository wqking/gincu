#ifndef MATCHTHREECHESS_H
#define MATCHTHREECHESS_H

#include "engine/geometry.h"
#include "engine/gameimage.h"

#include <string>

namespace gincu {

enum class ChessColor
{
	normal0,
	normal1,
	normal2,
	normal3,
	normal4,

	count,

	none
};

GameImage getChessResource(const ChessColor chessColor);
ChessColor randomChessColor();
bool areCellsNeighbors(const RowColumn & cellA, const RowColumn & cellB);


} //namespace gincu

#endif
