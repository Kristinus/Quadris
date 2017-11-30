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


void Block::updateSetCells(size_t rowsToDelete) {
	for (int i = cells.size() - 1; i >= 0; i--) {
	 		// if the row goes out of bounds, then erase the cell
	 		if (cells[i].getInfo().row - rowsToDelete < 0) {
	 			cells.erase(cells.begin() + i);

	 		} else {
	 			// decrement each setBlock's

	 			cells[i].moveDown(rowsToDelete);	
	 			// block->cells.block->cells.getInfo().row - rowsToDelete;
	 		}
	 	}
}

std::vector<Cell> Block::getBlockCells() {
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

void Block::left(int x){
   col--;
   move(-1, 0);
}

void Block::right(int x) {
   col++;
   move(1,0);
}

void Block::down(int x){
	row--;
   	move(0,-1);
}
