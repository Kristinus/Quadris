#include "block.h"
#include "grid.h"
#include "info.h"
#include <utility>

using namespace std;

Block::Block(BlockType blockType, int level, bool isHeavy): isHeavy{isHeavy}, level{level}, 
col{0}, row{0}, blockType{blockType} {
}


Block::Block(const Block &b):
cells{b.cells}, isHeavy{b.isHeavy}, level{b.level}, row{b.row},col{b.col}, grid{b.grid}, type{b.type}, blockType{b.blockType} {}


Block::~Block(){
	cells.clear();
}

void Block::updateSetCells(std::vector<int> rowsToDelete) {
	bool deleted;
	int drop;
	for (int i=cells.size()-1; i>=0; i--) {
		deleted = false;
		drop = 0;
		for(int r=0; r< rowsToDelete.size(); r++) {
			// if the row goes out of bounds, then erase the cell
			if (cells[i].getInfo().row == rowsToDelete[r]) {
				deleted = true;
				break;
			}
			else if(cells[i].getInfo().row > rowsToDelete[r])
				drop++;
		}
		if(deleted)
			cells.erase(cells.begin() + i);
		else
			cells[i].moveDown(drop);	
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

// 
void Block::move(int colshift, int rowshift) {
	for (auto &c : cells) {
		unsigned int oldcol = c.getInfo().col;
		unsigned int oldrow = c.getInfo().row;
		unsigned int newcol = oldcol + colshift;
		unsigned int newrow = oldrow + rowshift;
		c.setCoords(newrow, newcol);
	}
	for (auto &c: getBlockCells()) {
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

	row--;
	move(0,-1);

   			// for (auto c: getBlockCells()) {
		// cout << "DOWN(" << c.getInfo().row << "," << c.getInfo().col << ")" << endl;
	// }
}

bool Block::isValidCoordinate(int row, int col) {
//	if (grid == nullptr) {cout << "ITS NULL";}
	if ((col < 0) || (col >= 11) || (row < 0) || (row > 18) || 
		grid->getGridCells()[17 - row][col].getInfo().state == StateType::STATIC) {	
		return false;
}
else return true;
}


// moves the block to a specific coordinate based on bottom left coordinates
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

	for (int i = 1; i < cells.size(); i++) {
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
	for (int i = 0; i < cells.size(); i++) {
		rotatedCol[i] += deltax;
		rotatedRow[i] += deltay;

	}
	//(TODO) SHOULD BE IS VALID ROTATION
	if (!isValidRotation(this, rotatedRow, rotatedCol)) {
		return;
	} else {
		for (int i = 0; i < cells.size(); i++) {
			cells[i].setCoords(rotatedRow[i], rotatedCol[i]);

		}
		// update the bottom left coordinates
		row = oldBottomLeftRow;
		col = oldBottomLeftCol;

	}

}

bool Block::isValidRotation(Block *b, std::vector<int> rotatedRow, std::vector<int> rotatedCol) {
		// check that EACH rotated cell is valid
	for (int i = 0; i < b->cells.size(); i++) {
		// should be able to rotate onto hint blocks
		if (b->cells[i].getInfo().block != BlockType::HINT &&
			!isValidCoordinate(rotatedRow[i], rotatedCol[i])) {
			return false;
			// or we can throw an exception!!!!!!!!!!1
	}
}
return true;
}



//(TODO) make this prettier.. TWO OPTIONAL APRAMES?/?
void Block::setBlockCellStates(StateType s) {
	for (auto &c : cells) {
		c.setState(s);
	}
}

void Block::setBlockCellTypes(BlockType b) {
	for (auto &c : cells) {
		c.setBlock(b);
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
	return blockType;
}


std::ostream &operator<<(std::ostream &out, Block *b) {
	//Assuming first cell is top left and last cell is bottom right
	int i=0;
	unsigned int row=1;
	// out << "(" << row << "," << b->cells[i].getInfo().col << ")" << std::endl;
	for(unsigned int r=0; r<2; r++) {
		// out << "|" << i << "|" << std::endl;
		for(unsigned int c=0; c<4; c++) {
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
