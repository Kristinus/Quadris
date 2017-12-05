#include "block.h"
#include "info.h"
#include "constants.h"
#include "grid.h"

using namespace std;


Block::Block(BlockType blockType, int level, bool isHeavy): isHeavy{isHeavy}, 
level{level}, col{0}, row{0}, blockType{blockType} {}


Block::~Block(){
	cells.clear();
}


// takes a vector of indices that should be deleted and
// updates the cells of each block that is already set
void Block::updateSetCells(std::vector<size_t> rowsToDelete) {
	bool deleted;
	int drop;
	for (int i=cells.size()-1; i>=0; i--) {
		deleted = false;
		drop = 0;
		for(size_t r=0; r< rowsToDelete.size(); r++) {
			// if the row goes out of bounds, then erase the cell
			if (cells[i].getInfo().row == rowsToDelete[r]) {
				deleted = true;
				break;
			}
			else if(cells[i].getInfo().row > rowsToDelete[r])
				drop++;
		}
		if (deleted)
			cells.erase(cells.begin() + i);
		else
			cells[i].moveDown(drop);	
	}
}


std::vector<Cell> Block::getBlockCells() {
	return cells;
}


bool Block::isBlockHeavy() const {
	return isHeavy;
}


int Block::getLevel() const {
	return level;
}


// Moves block by the given vertical & horizontal magnitudes
void Block::move(int colshift, int rowshift) {
	for (auto &c : cells) {
		unsigned int oldcol = c.getInfo().col;
		unsigned int oldrow = c.getInfo().row;
		unsigned int newcol = oldcol + colshift;
		unsigned int newrow = oldrow + rowshift;
		c.setCoords(newrow, newcol);
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


// checks if coordinate is on grid and is unoccupied
bool Block::isValidCoordinate(int row, int col, Grid *grid) const {
	if ((col < 0) || (col >= constants::GRID_WIDTH) || (row < 0) || (row > constants::GRID_HEIGHT) || 
		grid->getGridCells()[constants::GRID_HEIGHT - 1 - row][col].getInfo().state == StateType::STATIC) {	
		return false;
   }
   else return true;
}


// Moves the block to a specific coordinate based on bottom left coordinates
void Block::moveTo(int bottomLeftRow, int bottomLeftCol) {
	int oldBottomLeftRow = row;
	int oldBottomLeftCol = col;
	int deltaRow = bottomLeftRow - oldBottomLeftRow;
	int deltaCol = bottomLeftCol - oldBottomLeftCol;

	for (auto &c : cells) {
		c.setCoords(c.getInfo().row + deltaRow, c.getInfo().col + deltaCol);
	}

	row = bottomLeftRow;
	col = bottomLeftCol;
}


// rotates the block 90 degrees in a specified direction
// +1 for clockwise, -1 for counterclockwise
void Block::rotate(int dir, Grid *grid) {
	std::vector<int> rotatedCol;
	std::vector<int> rotatedRow;
	int oldBottomLeftCol = col;
	int oldBottomLeftRow = row;

	int newBottomLeftCol = cells[0].getInfo().row * dir;
	int newBottomLeftRow = cells[0].getInfo().col * -dir;
	rotatedCol.emplace_back(newBottomLeftCol);
	rotatedRow.emplace_back(newBottomLeftRow);

	for (size_t i = 1; i < cells.size(); i++) {
		rotatedCol.emplace_back(cells[i].getInfo().row * dir);
		rotatedRow.emplace_back(cells[i].getInfo().col * -dir);

		// calculate the bottom left by taking the min of
		// all the row coordinates and col coordinates
		if (rotatedCol[i] < newBottomLeftCol) {
			newBottomLeftCol = rotatedCol[i];
		}

		if (rotatedRow[i] < newBottomLeftRow) {
			newBottomLeftRow = rotatedRow[i];
		}
	}

	// find the amount of moves that need to be done
	// to get the rotated block back to its bottom left corner
	int deltax = oldBottomLeftCol - newBottomLeftCol;
	int deltay = oldBottomLeftRow - newBottomLeftRow;

	// Update all cells
	for (size_t i = 0; i < cells.size(); i++) {
		rotatedCol[i] += deltax;
		rotatedRow[i] += deltay;

	}

	// ensure that the rotation is valid, otherwise
	// do nothing
	if (!isValidRotation(this, rotatedRow, rotatedCol, grid)) {
		return;
	} else {
		for (size_t i = 0; i < cells.size(); i++) {
			cells[i].setCoords(rotatedRow[i], rotatedCol[i]);
		}

		// Update the bottom left coordinates
		row = oldBottomLeftRow;
		col = oldBottomLeftCol;
	}
}


bool Block::isValidRotation(Block *b, std::vector<int> rotatedRow, 
	std::vector<int> rotatedCol, Grid *grid) {

	// Check that EACH rotated cell is valid
	for (size_t i = 0; i < b->cells.size(); i++) {

      // Should be able to rotate onto hint blocks
      if (b->cells[i].getInfo().block != BlockType::HINT && 
      	!isValidCoordinate(rotatedRow[i], rotatedCol[i], grid)) {
			return false;
	   }
   }
   return true;
}


void Block::clockwise(Grid *grid, int x) {
	x = x % 4;

	while (x > 0) {
		rotate(1, grid);
		x--;
	}
}


void Block::counterclockwise(Grid *grid, int x) {
	x = x % 4;

	while (x > 0) {
		rotate(-1, grid);
		x--;
	}
}


int Block::getBottomLeftCol() const {
	return col;
}


int Block::getBottomLeftRow() const {
	return row;
}


BlockType Block::getBlockType() const {
	return blockType;
}


std::ostream &operator<<(std::ostream &out, Block *b) {
	//print in a 4x4 box
	bool printed = false;
	size_t row = b->getBottomLeftRow();
	size_t col = b->getBottomLeftCol();

	for(size_t r=0 ; r<4 ; r++) {
		for(size_t c=0 ; c<4 ; c++) {
			printed = false;
			for(int i=0; i<4; i++) {
				if(b->cells[i].getInfo().row-row == 3-r && b->cells[i].getInfo().col-col == c) {
					out << b->type;
					printed = true;
					break;
				}
			}
			if(!printed) out << ' ';
		}
		out << std::endl;
	}
	return out;
}
