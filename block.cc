#include "block.h"
#include "grid.h"

using namespace std;

Block::Block(bool isHeavy): isHeavy{isHeavy} {
}

Block::Block(int col, int row, bool isHeavy, int level, vector<Cell> cells, Grid *theGrid): cells{cells}, isHeavy{isHeavy}, level{level}, col{col}, row{row}, grid{theGrid} {}

/**
Block::Block(bool isHeavy, int level, vector<Cell> cells): cells{cells}, isHeavy{isHeavy}, level{level} {
   col = 0;
   row = 0;
}
 **/
Block::~Block(){
   cells.clear();
}

vector<Cell> Block::getBlockCells() {
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
		size_t oldX = c.getInfo().col;
		size_t oldY = c.getInfo().row;
		size_t newX = oldX + offsetX;
		size_t newY = oldY + offsetY;
		c.setCoords(newX, newY);
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

