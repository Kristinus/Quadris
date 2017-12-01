#include "grid.h"
#include <cmath>
#include "cell.h"
#include "blocks.h"
#include <vector>
#include "info.h"
#include "levels.h"

Grid::Grid() {
// NEED TO FIGURE THIS SHIT OUT
  theLevel = new Level0();
  theScore = new Score();
  td = new TextDisplay(this);
//  std::vector<Block *> setBlocks;
//   ob = new GraphicsDisplay(this);
	initGrid();
}

std::vector<std::vector<Cell>> Grid::getGridCells() {
	return theGrid;
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
	// theGrid = res; (TODO)

	currentBlock = theLevel->createBlock();
	theGrid[5][5].setBlock(BlockType::J);
	theGrid[5][5].setState(StateType::MOVING);

	theGrid[5][5].notifyObservers();
	moveTo(15, 0, currentBlock);
	playBlock(currentBlock);
	nextBlock = theLevel->createBlock();

}

bool Grid::isOver() {
	// if the piece in play cannot be played

	// if (theScore->getCurrentScore > theScore->getHighScore) {
	// 	theScore->setHighScore(theScore->getCurrentScore);
	// }
	return false;
}

//Checks if the row is filled
bool Grid::isFilled(std::vector<Cell> row) {
	for (auto c : row) {
		if (c.getInfo().state != StateType::STATIC) return false;
	}
	return true;
}

/**
bool Grid::updateMovingBlock(std::vector<Cell> cells) {

	// (TODO) if we do cell pointers change this shitty run time

	for (int i = 0; i < theGrid.size(); i++) {
		for (int j = 0; j < theGrid[i].size(); j++) {
			for (auto c : cells) {
				if (c.getInfo().row == i && c.getInfo().col == j) {
					c.setBlock(currentBlock->getBlockType());
					c.setState(StateType::MOVING);
				} 
			}
		}
	}
	for (auto c : cells) {
		theGrid[c.getInfo().row][c.getInfo().col].setBlock(BlockType::MOVING);
	}
} **/


int Grid::countCompleteLines() {
	int rowsToDelete = 0;
	for (int i = theGrid.size() - 1; i >= 0; i--) {
		if (isFilled(theGrid[i])) {
			rowsToDelete++;
		}
	} 
	return rowsToDelete;
}

double Grid::calculateSmoothness() {
	std::vector<int> heights = getHeights();
	double stdHeights = getStandardDeviationHeights(heights);
	return stdHeights;

}


double Grid::getAverageHeights(std::vector<int> v) {      int sum=0;
       for(unsigned int i=0;i<v.size();i++)
               sum+=v[i];
       return sum/v.size();
}
//DEVIATION
double Grid::getStandardDeviationHeights(std::vector<int> v) {
		double ave = getAverageHeights(v);
       double E=0;
       for(unsigned int i=0;i<v.size();i++)
               E+=(v[i] - ave)*(v[i] - ave);
       return sqrt(1/v.size()*E);
}

std::vector<int> Grid::getHeights() {
	std::vector<int> heights(11);
	for (unsigned int row = theGrid.size() - 1; row >= 0; row--) {
		for (unsigned int col = 0; col < theGrid[col].size(); col++) {
			// record the index of the highest static block...if no block is there... height is 0
			if (theGrid[row][col].getInfo().state == StateType::STATIC) {
				heights[col] = theGrid[row][col].getInfo().col + 1;
			}
		}
	}

	return heights;
}

void Grid::moveTo(int bottomLeftRow, int bottomLeftCol, Block *b) {
	int oldBottomLeftRow = b->getBottomLeftRow();
	int oldBottomLeftCol = b->getBottomLeftCol();
	int deltaRow = bottomLeftRow - oldBottomLeftRow;
	int deltaCol = bottomLeftCol - oldBottomLeftCol;

	for (auto &c : b->getBlockCells()) {
		c.setCoords(c.getInfo().row + deltaRow, c.getInfo().col + deltaCol);

	}
	b->setBottomLeftCoords(bottomLeftRow, bottomLeftCol);


}

void Grid::playBlock(Block *b) {
	for (auto &c : b->getBlockCells()) {
		c.setState(StateType::MOVING);
		c.setBlock(b->getBlockType());
		c.notifyObservers();
	}

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

void Grid::deleteCurrentBlock() {
	for (int i = 0; i < currentBlock->getBlockCells().size(); i++) {
		int row = currentBlock->getBlockCells()[i].getInfo().row;
		int col = currentBlock->getBlockCells()[i].getInfo().col;
		theGrid[row][col].setBlock(BlockType::NONE);
		theGrid[row][col].setState(StateType::NONE);
	}
}



void Grid::left(int x) {
	deleteCurrentBlock();
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

	playBlock(currentBlock);


}

void Grid::right(int x) {
	deleteCurrentBlock();
	int shift = 0;
	while (shift < x) {
		if (isValidMove(currentBlock->getBlockCells(), 1, 0)) {
			currentBlock->right();
		} else {
			break;
		}
		shift++;
	}
	playBlock(currentBlock);

}
void Grid::down(int x) {
	deleteCurrentBlock();
	int shift = 0;
	while (shift < x) {
		if (isValidMove(currentBlock->getBlockCells(), 0, -1)) {
			currentBlock->down();
		} else {
			break;
		}
		shift++;
	}
	playBlock(currentBlock);
}

void Grid::setBlock(Block *curBlock) {
	for (auto cell : currentBlock->getBlockCells()) {
		theGrid[cell.getInfo().row][cell.getInfo().col].setState(StateType::STATIC);
		theGrid[cell.getInfo().row][cell.getInfo().col].notifyObservers();

	}
	setBlocks.emplace_back(currentBlock);

}

void Grid::unsetBlock(Block *block) {
	//(TODO)
	// for (auto cell : block->getBlockCells()) {
	// 	theGrid[cell.getInfo().row][cell.getInfo().col].setState(StateType::NONE);
	// }
	// setBlocks.pop_back();
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
		playBlock(currentBlock);

	}
	
	currentBlock = nextBlock;
	nextBlock = theLevel->createBlock();
	playBlock(currentBlock);

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
    playBlock(currentBlock);
    nextBlock = theLevel->createBlock();
    theScore->setCurrentScore(0);  

}
void Grid::rotateCW(int x) {
	deleteCurrentBlock();
	while (x > 0) {

		currentBlock->clockwise(x);

		x--;
	}
	playBlock(currentBlock);

}
void Grid::rotateCCW(int x) {
	deleteCurrentBlock();
	while (x > 0) {
		currentBlock->counterclockwise(x);
		x--;

	}
	playBlock(currentBlock);

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

int Grid::countHoles() {
	std::vector<int> heights = getHeights();
	int numHoles = 0; 
	// for all the cells below the highest cell
	for (unsigned int i = 0; i < heights.size(); i++) {
		for (int row = 0; row < heights[i]; row++) {
			if (theGrid[row][i].getInfo().state == StateType::NONE) {
				numHoles++;
			}
		}
	}

	return numHoles;

}
struct HintInfo {
	int bottomLeftRow;
	int bottomLeftCol;
	int numRotations;
	double priority;
	HintInfo(int blr, int blc, int nr, double p): bottomLeftRow{blr}, bottomLeftCol{blc},
	numRotations{nr}, priority{p} {

	}

};

void Grid::hint() {

	// MAKE SURE TO RESET HINTINFO
	// RESET THE HINT BLOCK
	// CODE THE MOVE TO HINT INFO WITH ROTATIONS AND TRANSLATIONS

	std::vector<HintInfo> hintInfo;

	Block temp{*currentBlock}; // implement the Copy Ctor
	hintBlock = &temp;

	for (unsigned int i = 0; i < 4; i++) {
		try {
			hintBlock->clockwise(i);
		} catch (...) { // rotaetfailexception
			continue;
		}

		int horizontal = 0;

		while (isValidMove(hintBlock->getBlockCells(), horizontal, 0)) {
			hintBlock->move(horizontal, 0);
			while (isValidMove(hintBlock->getBlockCells(), 0, -1)) {
				hintBlock->move(0, -1);
			}

			setBlock(hintBlock);
			double smoothness = calculateSmoothness();
			int completeLines = countCompleteLines();
			int numHoles = countHoles();
			double priority = (1/ (1+smoothness)) * completeLines * 1/(numHoles+1);
			hintInfo.emplace_back(HintInfo{hintBlock->getBottomLeftRow(), hintBlock->getBottomLeftCol(), i, priority});
			unsetBlock(hintBlock);
			horizontal++;
		}
		horizontal = 0;

		//(TODO) refactor so that we can input horizontal and change direction :)


		int max = 0;
		HintInfo best{0,0,0,0};
		for (HintInfo h : hintInfo) {

			if (h.priority > max) {
				max = h.priority;
				best = h;
			}
		}


	}



	



}

Block * Grid::getNextBlock() {
	return nextBlock;
}

Score *Grid::getScore() {
	return theScore;
}

int Grid::getLevel() {
	return theLevel->getLevel();
}


std::ostream &operator<<(std::ostream &out, Grid &grid) {
	out << *(grid.td);
	return out;
}


