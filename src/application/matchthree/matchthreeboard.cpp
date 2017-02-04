#include "matchthree/matchthreeboard.h"
#include "matchthree/matchthreechess.h"
#include "matchthree/scenematchthree.h"
#include "framework/entity.h"
#include "framework/componentrender.h"
#include "framework/componenttransform.h"
#include "framework/componenttouchhandler.h"
#include "framework/componentanchor.h"
#include "matchthree/componentchess.h"
#include "matchthree/matchthreeconsts.h"

namespace gincu {

MatchThreeBoard::MatchThreeBoard(SceneMatchThree * scene)
	:
		scene(scene),
		columnCount(boardColumnCount),
		rowCount(boardRowCount),
		cellSize(boardCellSize),
		startX(boardStartX),
		startY(boardStartY)
{
	this->chessBoard.resize(rowCount);
	std::fill(this->chessBoard.begin(), this->chessBoard.end(), std::vector<Entity *>(this->columnCount));
}

MatchThreeBoard::~MatchThreeBoard()
{
}

Entity * MatchThreeBoard::getChessAt(const RowColumn & cell) const
{
	if(cell.column < 0 || cell.column >= this->getColumnCount()) {
		return nullptr;
	}
	if(cell.row < 0 || cell.row >= this->getRowCount()) {
		return nullptr;
	}

	return this->doReferenceChessAt(cell);
}

Entity * MatchThreeBoard::createChessAt(const RowColumn & cell, const ChessColor chessColor)
{
	Entity * & chessReference = this->doReferenceChessAt(cell);

	this->scene->removeEntity(chessReference);

	chessReference = this->scene->addEntity(
		(new Entity())
			->addComponent(createComponent<ComponentTransform>(this->getChessPositionAt(cell), 1.0f))
			->addComponent(createComponent<ComponentAnchor>(RenderAnchor_Center))
			->addComponent(createAndLoadImageComponent(getChessResourceName(chessColor)))
			->addComponent(createComponent<ComponentRendererTouchHandler>()->addOnTouch(cpgf::makeCallback(scene, &SceneMatchThree::onChessTouched)))
			->addComponent(createComponent<ComponentChess>(chessColor))
		);

	return chessReference;
}

Entity * MatchThreeBoard::swapChess(const RowColumn & cell, Entity * replacer)
{
	Entity * & chessReference = doReferenceChessAt(cell);
	Entity * result = chessReference;
	chessReference = replacer;
	return result;
}

void MatchThreeBoard::removeChess(const RowColumn & cell)
{
	Entity * & chessReference = this->doReferenceChessAt(cell);

	scene->removeEntity(chessReference);

	chessReference = nullptr;
}

GamePoint MatchThreeBoard::getChessPositionAt(const RowColumn & cell) const
{
	return GamePoint {
		this->startX + (CoordType)(cell.column * this->cellSize),
		this->startY + (CoordType)(cell.row * this->cellSize)
	};
}

RowColumn MatchThreeBoard::getChessCell(const Entity * chess) const
{
	RowColumn result;

	for(int row = 0; row < this->rowCount; ++row) {
		result.row = row;
		for(int column = 0; column < this->columnCount; ++column) {
			result.column = column;
			if(this->getChessAt(result) == chess) {
				return result;
			}
		}
	}

	return RowColumn { -1, -1 };
}

Entity * const & MatchThreeBoard::doReferenceChessAt(const RowColumn & cell) const
{
	return this->chessBoard[cell.row][cell.column];
}

Entity * & MatchThreeBoard::doReferenceChessAt(const RowColumn & cell)
{
	return this->chessBoard[cell.row][cell.column];
}


} //namespace gincu
