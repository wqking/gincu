#include "matchthree/matchthreechess.h"
#include "gincu/gerrorhandler.h"
#include "gincu/gresourcemanager.h"
#include "gincu/gatlas.h"
#include "gincu/gapplication.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gutil.h"

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

GComponentRender * createChessRender(const ChessColor chessColor)
{
	return createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas("matchthree/chess_atlas", GAtlasFormat::spritePackText), getChessResourceName(chessColor));
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
