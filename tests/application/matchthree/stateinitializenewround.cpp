#include "matchthree/stateinitializenewround.h"
#include "matchthree/matchthreestates.h"
#include "matchthree/matchthreeboard.h"
#include "matchthree/matchthreechess.h"
#include "matchthree/componentchess.h"
#include "matchthree/scenematchthree.h"
#include "gincu/gentity.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gutil.h"
#include "cpgf/tween/gtweenlist.h"
#include "cpgf/tween/easing/quad.h"
#include "cpgf/accessor/gaccessor.h"

namespace gincu {

StateInitializeNewRound::StateInitializeNewRound(SceneMatchThree * scene)
	: super(stateInitializeNewRound, stateCheckDeadBoard), scene(scene)
{

}

StateInitializeNewRound::~StateInitializeNewRound()
{

}

void StateInitializeNewRound::doOnEnter()
{
	MatchThreeBoard * board = this->scene->getBoard();

	cpgf::GTween & tween = getTweenListFromScene()->tween()
		.duration(500.0f) // 0.5 seconds
		.ease(cpgf::QuadEase::easeIn())
		.onComplete(cpgf::makeCallback(this, &StateInitializeNewRound::finish))
	;

	const int rowCount = board->getRowCount();
	const int columnCount = board->getColumnCount();

	for(int row = 0; row < rowCount; ++row) {
		for(int column = 0; column < columnCount; ++column) {
			const RowColumn rowColumn { row, column };
			
			ChessColor chessColor = randomChessColor();

			ChessColor avoidColor1 = ChessColor::none;
			ChessColor avoidColor2 = ChessColor::none;

			if(column >= 2) {
				const ChessColor color1 = board->getChessAt({ row, column - 1 })->getComponentByType<ComponentChess>()->getColor();
				const ChessColor color2 = board->getChessAt({ row, column - 2 })->getComponentByType<ComponentChess>()->getColor();
				if(color1 == color2) {
					avoidColor1 = color1;
				}
			}
			if(row >= 2) {
				const ChessColor color1 = board->getChessAt({ row - 1, column })->getComponentByType<ComponentChess>()->getColor();
				const ChessColor color2 = board->getChessAt({ row - 2, column })->getComponentByType<ComponentChess>()->getColor();
				if(color1 == color2) {
					avoidColor2 = color1;
				}
			}

			while(chessColor == avoidColor1 || chessColor == avoidColor2) {
				chessColor = randomChessColor();
			}

			GEntity * chess = board->createChessAt(rowColumn, chessColor);

			GComponentTransform * transform = chess->getComponentByType<GComponentTransform>();
			transform->setPosition(board->getChessPositionAt({ getRand(rowCount), getRand(columnCount) }));

			const GPoint position = board->getChessPositionAt(rowColumn);
			tween.target(cpgf::createAccessor(transform, &GComponentTransform::getPosition, &GComponentTransform::setPosition), position);
		}
	}
}

void StateInitializeNewRound::doOnExit()
{
}


} //namespace gincu
