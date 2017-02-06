#include "matchthree/matchthreeboard.h"
#include "matchthree/matchthreechess.h"
#include "matchthree/scenematchthree.h"
#include "matchthree/componentchess.h"
#include "matchthree/matchthreeconsts.h"
#include "gincu/gentity.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/gcomponentanchor.h"

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
	std::fill(this->chessBoard.begin(), this->chessBoard.end(), std::vector<GEntity *>(this->columnCount));
}

MatchThreeBoard::~MatchThreeBoard()
{
}

GEntity * MatchThreeBoard::getChessAt(const RowColumn & cell) const
{
	if(cell.column < 0 || cell.column >= this->getColumnCount()) {
		return nullptr;
	}
	if(cell.row < 0 || cell.row >= this->getRowCount()) {
		return nullptr;
	}

	return this->doReferenceChessAt(cell);
}

GEntity * MatchThreeBoard::createChessAt(const RowColumn & cell, const ChessColor chessColor)
{
	GEntity * & chessReference = this->doReferenceChessAt(cell);

	this->scene->removeEntity(chessReference);

	chessReference = this->scene->addEntity(
		(new GEntity())
			->addComponent(createComponent<GComponentTransform>(this->getChessPositionAt(cell)))
			->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
			->addComponent(createImageComponent(getChessResource(chessColor)))
			->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(cpgf::makeCallback(scene, &SceneMatchThree::onChessTouched)))
			->addComponent(createComponent<ComponentChess>(chessColor))
		);

	return chessReference;
}

GEntity * MatchThreeBoard::swapChess(const RowColumn & cell, GEntity * replacer)
{
	GEntity * & chessReference = doReferenceChessAt(cell);
	GEntity * result = chessReference;
	chessReference = replacer;
	return result;
}

void MatchThreeBoard::removeChess(const RowColumn & cell)
{
	GEntity * & chessReference = this->doReferenceChessAt(cell);

	scene->removeEntity(chessReference);

	chessReference = nullptr;
}

GPoint MatchThreeBoard::getChessPositionAt(const RowColumn & cell) const
{
	return GPoint {
		this->startX + (GCoord)(cell.column * this->cellSize),
		this->startY + (GCoord)(cell.row * this->cellSize)
	};
}

RowColumn MatchThreeBoard::getChessCell(const GEntity * chess) const
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

GEntity * const & MatchThreeBoard::doReferenceChessAt(const RowColumn & cell) const
{
	return this->chessBoard[cell.row][cell.column];
}

GEntity * & MatchThreeBoard::doReferenceChessAt(const RowColumn & cell)
{
	return this->chessBoard[cell.row][cell.column];
}


} //namespace gincu
