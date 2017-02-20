#include "matchthree/statecheckdeadboard.h"
#include "matchthree/matchthreestates.h"
#include "matchthree/matchthreeboard.h"
#include "matchthree/matchthreechess.h"
#include "matchthree/componentchess.h"
#include "matchthree/componentchess.h"
#include "matchthree/scenematchthree.h"
#include "gincu/gstatemachine.h"
#include "gincu/ecs/gentity.h"

#include <vector>

namespace gincu {

namespace {

typedef unsigned int LineType;

bool isLineSolvable(LineType line)
{
	while(line > 0) {
		if((line & 7) == 7) {
			return true;
		}
		line >>= 1;
	}
	return false;
}

// The algorithm assumes the board size <= (bits of LineType) so we can use integer bits to hold the cells.
bool isBoardSolvable(const MatchThreeBoard * board)
{
	using std::swap;

	const int rowCount = board->getRowCount();
	const int columnCount = board->getColumnCount();

	std::vector<LineType> previousChessLines((int)ChessColor::count);
	std::vector<LineType> chessLines((int)ChessColor::count);

	for(int row = 0; row < rowCount; ++row) {
		std::fill(chessLines.begin(), chessLines.end(), 0);

		for(int column = 0; column < columnCount; ++column) {
			const ChessColor color = board->getChessAt(RowColumn { row, column })->getComponentByType<ComponentChess>()->getColor();
			chessLines[(int)color] |= (1 << column);
		}

		if(row > 0) {
			for(int i = 0; i < (int)ChessColor::count; ++i) {
				if(isLineSolvable(previousChessLines[i] | chessLines[i])) {
					return true;
				}
			}
		}

		swap(previousChessLines, chessLines);
	}

	std::fill(previousChessLines.begin(), previousChessLines.end(), 0);

	for(int column = 0; column < columnCount; ++column) {
		std::fill(chessLines.begin(), chessLines.end(), 0);

		for(int row = 0; row < rowCount; ++row) {
			const ChessColor color = board->getChessAt(RowColumn { row, column })->getComponentByType<ComponentChess>()->getColor();
			chessLines[(int)color] |= (1 << row);
		}

		if(column > 0) {
			for(int i = 0; i < (int)ChessColor::count; ++i) {
				if(isLineSolvable(previousChessLines[i] | chessLines[i])) {
					return true;
				}
			}
		}

		swap(previousChessLines, chessLines);
	}

	return false;
}

}

StateCheckDeadBoard::StateCheckDeadBoard(SceneMatchThree * scene)
	: super(stateCheckDeadBoard, stateMainLoop), scene(scene)
{
}

StateCheckDeadBoard::~StateCheckDeadBoard()
{
}

void StateCheckDeadBoard::doOnEnter()
{
	if(isBoardSolvable(this->scene->getBoard())) {
		this->finish();
	}
	else {
		this->getStateMachine()->gotoState(stateInitializeNewRound);
	}
}

void StateCheckDeadBoard::doOnExit()
{
}


} //namespace gincu
