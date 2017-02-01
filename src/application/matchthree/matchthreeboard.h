#ifndef MATCHTHREEBOARD_H
#define MATCHTHREEBOARD_H

#include "engine/geometry.h"

#include <vector>

namespace gincu {

class SceneMatchThree;
class Entity;
enum class ChessColor;

class MatchThreeBoard
{
public:
	explicit MatchThreeBoard(SceneMatchThree * scene);
	~MatchThreeBoard();

	Entity * getChessAt(const RowColumn & cell) const;
	Entity * createChessAt(const RowColumn & cell, const ChessColor chessColor);
	GamePoint getChessPositionAt(const RowColumn & cell) const;

	Entity * swapChess(const RowColumn & cell, Entity * replacer);
	void removeChess(const RowColumn & cell);

	RowColumn getChessCell(const Entity * chess) const;

	int getColumnCount() const { return columnCount; }
	int getRowCount() const { return rowCount; }

private:
	Entity * const & doReferenceChessAt(const RowColumn & cell) const;
	Entity * & doReferenceChessAt(const RowColumn & cell);

private:
	SceneMatchThree * scene;

	int columnCount;
	int rowCount;
	int cellSize;
	int startX;
	int startY;

	std::vector<std::vector<Entity *> > chessBoard;
};


} //namespace gincu

#endif
