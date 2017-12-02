#include "block.h"
#include "grid.h"
#include "info.h"

using namespace std;

Block::Block(int level, bool isHeavy): isHeavy{isHeavy}, level{level}, row{0}, col{0} {
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


// going down is ADD
void Block::move(int colshift, int rowshift) {
	for (auto &c : cells) {
		size_t oldcol = c.getInfo().col;
		size_t oldrow = c.getInfo().row;
		size_t newcol = oldcol + colshift;
		size_t newrow = oldrow + rowshift;
		c.setCoords(newrow, newcol);
	}
			for (auto &c: getBlockCells()) {
		// cout << "MOVE(" << c.getInfo().row << "," << c.getInfo().col << ")" << endl;
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

void Block::setGridPointer(Grid *theGrid) {
	grid = theGrid;
}

void Block::displayNext(Observer<Info> *ob) {
	for(auto c:cells) {
		c.attach(ob);
		c.notifyObservers();
	}
}

void Block::down(int x){
	row++;
   	move(0,-1);
   			for (auto c: getBlockCells()) {
		// cout << "DOWN(" << c.getInfo().row << "," << c.getInfo().col << ")" << endl;
	}
}

bool Block::isValidCoordinate(int row , int col) {
	if (grid == nullptr) {cout << "ITS NULL";}
	cout << "VAID";
	cout << row << " IS row " << col << " IS cl" << endl;

	if ((col < 0) || (col >= 11) || (row < 0) || (row > 18)
		|| grid->getGridCells()[17 - row][col].getInfo().state == StateType::STATIC) {
		return false;
	} else return true;
}

void Block::setBottomLeftCoords(int row, int col) {
	row = row;
	col = col;
}

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

// delete this
void Block::playBlock() {
	for (auto &c : cells) {
		c.setState(StateType::MOVING);
		c.setBlock(getBlockType());
	}
}

void Block::rotate(int dir) {
	std::vector<int> rotatedCol;
	std::vector<int> rotatedRow;
	int oldBottomLeftCol = col;
	int oldBottomLeftRow = row;

	int newBottomLeftCol = cells[0].getInfo().row * dir;
	int newBottomLeftRow = cells[0].getInfo().col * -dir;
	rotatedCol.emplace_back(newBottomLeftCol);
	rotatedRow.emplace_back(newBottomLeftRow);

	for (unsigned int i = 1; i < cells.size(); i++) {
		rotatedCol.emplace_back(cells[i].getInfo().row * dir);
		rotatedRow.emplace_back(cells[i].getInfo().col * -dir);

		// get the min bottom of left by getting the leftmost coord and the bottom most
		if (rotatedCol[i] < newBottomLeftCol) {
			newBottomLeftCol = rotatedCol[i];
		}
		if (rotatedRow[i] < newBottomLeftRow) {
			newBottomLeftRow = rotatedRow[i];
		}
	}


	// get the delta from the old bottom left
	int deltax = oldBottomLeftCol - newBottomLeftCol;
	int deltay = oldBottomLeftRow - newBottomLeftRow;

	// update all cells
	for (unsigned int i = 0; i < cells.size(); i++) {
		rotatedCol[i] += deltax;
		rotatedRow[i] += deltay;

	}


	//if (grid == nullptr) cout << "its null" << endl;
	for (unsigned int i = 0; i < cells.size(); i++) {
		cout << "WHA";
		if (!isValidCoordinate(rotatedRow[i], rotatedCol[i])) {
			return;
			// or we can throw an exception!!!!!!!!!!1
		}
		cells[i].setCoords(rotatedRow[i], rotatedCol[i]);

	}

	//updat


	// update the new bottomleft coordinates
	row = oldBottomLeftRow;
	col = oldBottomLeftCol;

}

void Block::setBlockCellStates(StateType s) {
	for (auto &c : cells) {
		c.setState(s);
	}
}

void Block::clockwise(int x) {
	x = x%4;
	while (x > 0) {
		
		rotate(1);

		x--;

	}

}

void Block::counterclockwise(int x) {
	x = x%4;
	while (x > 0) {
		rotate(-1);
		x--;

	}
}

int Block::getBottomLeftCol() {
	return col;
}

int Block::getBottomLeftRow() {
	return row;
}

//(TODO) figure out pure virtual for this!!!!!!
BlockType Block::getBlockType() {
	return BlockType::NONE;
}


std::ostream &operator<<(std::ostream &out, Block *b) {
	//Assuming first cell is top left and last cell is bottom right
	int i=0;
	size_t row=1;
	// out << "(" << row << "," << b->cells[i].getInfo().col << ")" << std::endl;
	for(size_t r=0; r<2; r++) {
		// out << "|" << i << "|" << std::endl;
		for(size_t c=0; c<4; c++) {
			// out << "|" << i << "|" << std::endl;
			if(b->cells[i].getInfo().row == row-r && b->cells[i].getInfo().col == c) {
				out << b->type;
				i++;
				if(i==4) break;
			}
			else out << ' ';
		}
		out << std::endl;
	}
	return out;
}
