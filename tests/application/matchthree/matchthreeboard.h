#ifndef MATCHTHREEBOARD_H
#define MATCHTHREEBOARD_H

#include "gincu/ggeometry.h"

#include <vector>

namespace gincu {

class SceneMatchThree;
class GEntity;
enum class ChessColor;

class MatchThreeBoard
{
public:
	explicit MatchThreeBoard(SceneMatchThree * scene);
	~MatchThreeBoard();

	GEntity * getChessAt(const RowColumn & cell) const;
	GEntity * createChessAt(const RowColumn & cell, const ChessColor chessColor);
	GPoint getChessPositionAt(const RowColumn & cell) const;

	GEntity * swapChess(const RowColumn & cell, GEntity * replacer);
	void removeChess(const RowColumn & cell);

	RowColumn getChessCell(const GEntity * chess) const;

	int getColumnCount() const { return columnCount; }
	int getRowCount() const { return rowCount; }

private:
	GEntity * const & doReferenceChessAt(const RowColumn & cell) const;
	GEntity * & doReferenceChessAt(const RowColumn & cell);

private:
	SceneMatchThree * scene;

	int columnCount;
	int rowCount;
	int cellSize;
	int startX;
	int startY;

	std::vector<std::vector<GEntity *> > chessBoard;
};


} //namespace gincu

#endif
