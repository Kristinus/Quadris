#include "block.h"

using namespace std;

Block::Block(int col, int row, bool isHeavy, vector<Cell> cells): cells{cells}, isHeavy{isHeavy}, level{level}, col{col}, row{row}, theGrid{theGrid} {}

/**
Block::Block(bool isHeavy, int level, vector<Cell> cells): cells{cells}, isHeavy{isHeavy}, level{level} {
   col = 0;
   row = 0;
}
 **/
Block::~Block(){
   cells.clear();
}

vector<Cell *> Block::getBlockCells() {
   return cells;
}

bool Block::isBlockHeavy(){
   return isHeavy;
}

int Block::getLevel(){
   return level;
}

void Block::move(int offsetX, int offsetY) {
	for (auto &c : cells) {
		size_t oldX = c.info.col;
		size_t oldY = c.info.row;
		size_t newX = oldX + offsetX;
		size_t newY = oldY + offsetY;
		theGrid->cells[oldY][oldX].setState(StateType::NONE);
		theGrid->cells[newY][newX].setState(StateType::MOVING);
		c.info.col = newX;
		c.info.row = newY;
	}
}

void Block::left(){
   col--;
   move(-1, 0);
}

void Block::right() {
   col++;
   move(1,0);
}

void Block::down(){
	row--;
   	move(0,-1);
}

