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


void Block::updateSetCells(int rowsToDelete) {
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

bool isValidCoordinate(Grid* theGrid, int x, int y) {
	if ((x >= 0) && (x <= 11) && (y >=0) && (y <= 18)
		&& theGrid->getGridCells()[y][x].getInfo().state != StateType::STATIC) {
		return true;
	} else return false;
}

void Block::rotate(int dir) {
	int[] rotatedX = int[cells.size()];
	int[] rotatedY = int[cells.size()];
	int oldBottomLeftX = col;
	int oldBottomRightY = row;

	int newBottomLeftX = cells[0].getInfo().row * dir;
	int newBottomLeftY = cells[0].getInfo().col * -dir;
	rotatedX[0] = newBottomLeftX;
	rotatedY[0] = newBottomLeftY;

	for (int i = 1; i < cells.size(); i++) {
		rotatedX[i] = cells[i].getInfo().row * dir;
		rotatedY[i] = cells[i].getInfo().col * -dir;

		// get the min bottom of left by getting the leftmost coord and the bottom most
		if (rotatedX[i] < newBottomLeftX) {
			newBottomLeftX = rotatedX[i];
		}
		if (rotatedY[i] < newBottomLeftY) {
			newBottomLeftY = rotatedY[i];
		}
	}

	// get the delta from the old bottom left
	int deltax = oldBottomLeftX - newBottomLeftX;
	int deltay = oldBottomRightY - newBottomLeftY;

	// update all cells
	for (int i = 0; i < cells.size(); i++) {
		rotatedX[i] += deltax;
		rotatedY[i] += deltay;
		if (!isValidCoordinate(theGrid, rotatedX[i], rotatedY[i])) {
			return; // or we can throw an exception!!!!!!!!!!1
		}
	}
	// modify the cell
	for (int i = 0; i < cells.size(); i++) {
		cells[i].setCoords(rotatedY[i], rotatedX[i]);
	}

}

void Block::clockwise() {
	rotate(1);

}

void Block::counterclockwise() {
	rotate(-1);
}

