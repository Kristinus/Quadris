#include "grid.h"
#include <cmath>
#include "cell.h"
#include "blocks.h"
#include <vector>
#include "info.h"

Grid::Grid():td{new TextDisplay(this)} {
// NEED TO FIGURE THIS SHIT OUT
  theLevel = nullptr;
  theScore = nullptr;
//  std::vector<Block *> setBlocks;
//   ob = new GraphicsDisplay(this);
	initGrid();
}


void Grid::initGrid() {
	theGrid.clear();
	

	for (int i = 0; i < 18; i++) {
		std::vector<Cell> row;
		for (int j = 0; j < 11; j++) {
			Info info;
			info.row = i;
			info.col = j;
			info.block = BlockType::NONE;
			info.state = StateType::NONE;
			Cell c = Cell(info);
			c.attach(td);
			c.attach(ob);
			row.emplace_back(Cell(info));
		}
		// adds each row to the beginning so the bottom left is the ORIGIN (0,0)
		theGrid.insert(theGrid.begin(), row);
	}
	// theGrid = res; ?????

}

bool Grid::isOver() {
	// if the piece in play cannot be played

	// if (theScore->getCurrentScore > theScore->getHighScore) {
	// 	theScore->setHighScore(theScore->getCurrentScore);
	// }
	return false;
}

//Checks if the row is filled
bool isFilled(std::vector<Cell> row) {
	for (auto c : row) {
		if (c.getInfo().state != StateType::STATIC) return false;
	}
	return true;
}

void Grid::deleteRow() {
	int rowsToDelete = 0;
	for (int i = theGrid.size() - 1; i >= 0; i--) {
		if (isFilled(theGrid[i])) {
			theGrid.erase(theGrid.begin() + i);
			rowsToDelete++;
		}
	}

	for (auto row : theGrid) {
		for (auto c: row) {
			c.setCoords(c.getInfo().row - rowsToDelete, c.getInfo().col);
		}
	}

	//Recreate Rows
	for (int i = rowsToDelete - 1; i >= 0; i++) {
		std::vector<Cell> row;
		for (int j = 0; j < 11; j++) {
			Info info;
			info.row = 17 - i;
			info.col = j;
			info.state = StateType::NONE;
			info.block = BlockType::NONE;
			Cell c = Cell{info};
			row.emplace_back(c);
		}
		theGrid.insert(theGrid.begin(), row);
	}

//	Delete Cells from Block if in deleted row
//	Decrement cell.row in each block


	 // iterate through each block pointer
	 for (size_t i=0; i<setBlocks.size(); i++) {
	 	// iterate through each block's cells
	 	// removes cells that are out of bounds, or sets them to the new location
	 	setBlocks[i]->updateSetCells(rowsToDelete);
	 	if (setBlocks[i]->getBlockCells().size() == 0) {
	 		theScore->addToCurrentScore(pow((setBlocks[i]->getLevel() + 1), 2));
	 		delete setBlocks[i];
	 		setBlocks.erase(setBlocks.begin() + i);
	 	}
	
	 }

	theScore->addToCurrentScore(pow(theLevel->getLevel() + rowsToDelete, 2));

}

bool Grid::isValidMove(std::vector<Cell> theCells, int offsetX, int offsetY) {
	for (auto &cell: theCells) {
		int newX = cell.getInfo().row + offsetX;
		int newY = cell.getInfo().col + offsetY;

		if (!((newX >= 0 && (newX <= 11) && (newY >= 0)
			&& theGrid[newX][newY].getInfo().state != StateType::STATIC))) {
			return false;
		}
	}
	return true;	
}


void Grid::left(int x) {
	// check if valid move
	// update the current block's cells
	int shift = 0;
	while (shift < x) {
		if (isValidMove(currentBlock->getBlockCells(), -1, 0)) {
			currentBlock->left();
		} else {
			break;
		}
		shift++;
	}


}

void Grid::right(int x) {

	int shift = 0;
	while (shift < x) {
		if (isValidMove(currentBlock->getBlockCells(), 1, 0)) {
			currentBlock->right();
		} else {
			break;
		}
		shift++;
	}

}
void Grid::down(int x) {
	int shift = 0;
	while (shift < x) {
		if (isValidMove(currentBlock->getBlockCells(), 0, -1)) {
			currentBlock->down();
		} else {
			break;
		}
		shift++;
	}
}

void Grid::setBlock(Block *curBlock) {
	for (auto cell : currentBlock->getBlockCells()) {
		theGrid[cell.getInfo().row][cell.getInfo().col].setState(StateType::STATIC);
	}
	setBlocks.emplace_back(currentBlock);
}

void Grid::drop(int x) {
	while (x > 0) {
		while (isValidMove(currentBlock->getBlockCells(), 0, -1)) {
			currentBlock->down();
		}
		setBlock(currentBlock);
		x--;
		currentBlock = nextBlock;
		nextBlock = theLevel->createBlock();

	}
	
	currentBlock = nextBlock;
	nextBlock = theLevel->createBlock();

}

void Grid::restart() {
	for (auto b : setBlocks) {
		delete b;
	}

    delete currentBlock;
    delete nextBlock;
    // note: level doesn't change
    initGrid(); 
    currentBlock = theLevel->createBlock();
    nextBlock = theLevel->createBlock();
    theScore->setCurrentScore(0);  

}
void Grid::rotateCW(int x) {
	while (x > 0) {
		currentBlock->clockwise(x);
		x--;
	}

}
void Grid::rotateCCW(int x) {
	while (x > 0) {
		currentBlock->counterclockwise(x);
	}

}
void Grid::levelUp(int x) {
	while (x > 0) {
		theLevel->levelUp();
		x--;
	}

}
void Grid::levelDown(int x) {
	while (x > 0) {
		theLevel->levelDown();
		x--;
	}

}
void Grid::random(bool flag) {
	isRandom = flag;
}
void Grid::hint() {

}


std::ostream &operator<<(std::ostream &out, Grid &grid) {
	out << *(grid.td) << std::endl;
	return out;
}


