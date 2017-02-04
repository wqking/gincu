#include "matchthree/matchthreechess.h"
#include "engine/errorhandler.h"
#include "engine/resourcemanager.h"
#include "engine/gamespritesheet.h"
#include "framework/gameapplication.h"
#include "framework/util.h"

#include <map>
#include <cmath>

namespace gincu {

namespace {

const std::map<ChessColor, std::string> chessColorResourceMap {
	{ ChessColor::normal0, "1" },
	{ ChessColor::normal1, "2" },
	{ ChessColor::normal2, "3" },
	{ ChessColor::normal3, "4" },
	{ ChessColor::normal4, "5" },
};

}

std::string getChessResourceName(const ChessColor chessColor)
{
	auto it = chessColorResourceMap.find(chessColor);
	if(it == chessColorResourceMap.end()) {
		handleFatal("Can't find chess color: " + toString((int)chessColor));
		return std::string();
	}
	return it->second;
}

GameImage getChessResource(const ChessColor chessColor)
{
	return ResourceManager::getInstance()->getSpriteSheet("matchthree/chess_spritesheet", SpriteSheetFormat::spritePackText)->getImage(getChessResourceName(chessColor));
}

ChessColor randomChessColor()
{
	return (ChessColor)((int)ChessColor::normal0 + getRand(0, (int)ChessColor::count));
}

bool areCellsNeighbors(const RowColumn & cellA, const RowColumn & cellB)
{
	if(cellA.row == cellB.row && std::abs(cellA.column - cellB.column) == 1) {
		return true;
	}
	else if(cellA.column == cellB.column && std::abs(cellA.row - cellB.row) == 1) {
		return true;
	}
	else {
		return false;
	}
}


} //namespace gincu
