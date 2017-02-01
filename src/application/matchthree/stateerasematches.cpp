#include "matchthree/stateerasematches.h"
#include "matchthree/matchthreestates.h"
#include "matchthree/matchthreeboard.h"
#include "matchthree/matchthreechess.h"
#include "matchthree/componentchess.h"
#include "matchthree/scenematchthree.h"
#include "framework/entity.h"
#include "framework/componenttransform.h"
#include "framework/statemachine.h"
#include "cpgf/tween/gtweenlist.h"
#include "cpgf/tween/easing/quad.h"
#include "cpgf/accessor/gaccessor.h"


namespace gincu {

StateEraseMatches::StateEraseMatches(SceneMatchThree * scene, const int stateId, const int nextStateId)
	: super(stateId, nextStateId), scene(scene)
{
}

StateEraseMatches::~StateEraseMatches()
{
}

void StateEraseMatches::doOnEnter()
{
	if(this->doFindAllMatches()) {
		this->animateToDisappear();
	}
	else {
		this->finish();
	}
}

void StateEraseMatches::doOnExit()
{
	this->matchedColumnRows.clear();
}

bool StateEraseMatches::doFindAllMatches()
{
	bool hasMatches = false;

	MatchThreeBoard * board = this->scene->getBoard();

	const int rowCount = board->getRowCount();
	const int columnCount = board->getColumnCount();

	this->matchedColumnRows.clear();
	this->matchedColumnRows.resize(columnCount);

	for(int row = 0; row < rowCount; ++row) {
		ComponentChess * chess1 = board->getChessAt(RowColumn { row, 0 })->getComponentByType<ComponentChess>();
		ComponentChess * chess2 = board->getChessAt(RowColumn { row, 1 })->getComponentByType<ComponentChess>();
		bool isFirst = true;
		for(int column = 2; column < columnCount; ++column) {
			ComponentChess * chess3 = board->getChessAt(RowColumn { row, column })->getComponentByType<ComponentChess>();
			if(chess1->getColor() == chess2->getColor() && chess2->getColor() == chess3->getColor()) {
				hasMatches = true;

				if(isFirst) {
					this->matchedColumnRows[column - 1].insert(row);
					this->matchedColumnRows[column - 2].insert(row);
					isFirst = false;
				}
				this->matchedColumnRows[column].insert(row);
			}
			else {
				isFirst = true;
			}
			chess1 = chess2;
			chess2 = chess3;
		}
	}

	for(int column = 0; column < columnCount; ++column) {
		ComponentChess * chess1 = board->getChessAt(RowColumn { 0, column })->getComponentByType<ComponentChess>();
		ComponentChess * chess2 = board->getChessAt(RowColumn { 1, column })->getComponentByType<ComponentChess>();
		bool isFirst = true;
		for(int row = 2; row < rowCount; ++row) {
			ComponentChess * chess3 = board->getChessAt(RowColumn { row, column })->getComponentByType<ComponentChess>();
			if(chess1->getColor() == chess2->getColor() && chess2->getColor() == chess3->getColor()) {
				hasMatches = true;

				if(isFirst) {
					this->matchedColumnRows[column].insert(row - 1);
					this->matchedColumnRows[column].insert(row - 2);
					isFirst = false;
				}
				this->matchedColumnRows[column].insert(row);
			}
			else {
				isFirst = true;
			}
			chess1 = chess2;
			chess2 = chess3;
		}
	}

	return hasMatches;
}

void StateEraseMatches::finishedMatch()
{
	this->getStateMachine()->gotoState(stateCheckEraseMatches);
}

void StateEraseMatches::animateToDisappear()
{
	MatchThreeBoard * board = this->scene->getBoard();

	cpgf::GTween & tween = cpgf::GTweenList::getInstance()->tween()
		.duration(200)
		.ease(cpgf::QuadEase::easeIn())
		.onComplete(cpgf::makeCallback(this, &StateEraseMatches::fullfilNewChesses))
	;

	for(int column = 0; column < (int)this->matchedColumnRows.size(); ++column) {
		const std::set<int> & rowSet = this->matchedColumnRows[column];
		for(auto it = rowSet.begin(); it != rowSet.end(); ++it) {
			const int row = *it;
			Entity * chess = board->getChessAt(RowColumn { row, column });
			ComponentTransform * transform = chess->getComponentByType<ComponentTransform>();
			tween.target(cpgf::createAccessor(transform, &ComponentTransform::getScale, &ComponentTransform::setScale), 0.1f);
		}
	}
}

void StateEraseMatches::fullfilNewChesses()
{
	MatchThreeBoard * board = this->scene->getBoard();
	const int rowCount = board->getRowCount();

	cpgf::GTween & tween = cpgf::GTweenList::getInstance()->tween()
		.duration(300)
		.ease(cpgf::QuadEase::easeIn())
		.onComplete(cpgf::makeCallback(this, &StateEraseMatches::finishedMatch))
		;

	int matchedCount = 0;
	for(int column = 0; column < (int)this->matchedColumnRows.size(); ++column) {
		const std::set<int> & rowSet = this->matchedColumnRows[column];
		for(auto it = rowSet.rbegin(); it != rowSet.rend(); ++it) {
			++matchedCount;
			board->removeChess(RowColumn { *it, column });
		}
	}

	const int score = 20 + (matchedCount - 3) * 10;

	scene->gotScore(score);

	for(int column = 0; column < (int)this->matchedColumnRows.size(); ++column) {
		const std::set<int> & rowSet = this->matchedColumnRows[column];
		int previousCheckedRow = rowCount;
		for(int row = rowCount - 1; row >= 0; --row) {
			const RowColumn currentCell { row, column };

			if(board->getChessAt(currentCell) != nullptr) {
				continue;
			}

			if(previousCheckedRow > row) {
				previousCheckedRow = row;
			}
			--previousCheckedRow;

			while(previousCheckedRow >= 0) {
				if(rowSet.find(previousCheckedRow) == rowSet.end()) {
					break;
				}
				--previousCheckedRow;
			}
			
			Entity * fullfilChess = nullptr;

			if(previousCheckedRow >= 0) {
				fullfilChess = board->swapChess(RowColumn { previousCheckedRow, column }, nullptr);
				board->swapChess(currentCell, fullfilChess);
			}
			else {
				fullfilChess = board->createChessAt(currentCell, randomChessColor());
			}

			ComponentTransform * transform = fullfilChess->getComponentByType<ComponentTransform>();
			if(previousCheckedRow < 0) {
				transform->setPosition(board->getChessPositionAt(RowColumn { -1, column }));
			}
			const GamePoint position = board->getChessPositionAt(currentCell);
			tween.target(cpgf::createAccessor(transform, &ComponentTransform::getPosition, &ComponentTransform::setPosition), position);
		}
	}
}


} //namespace gincu
