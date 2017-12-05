#include "grid.h"
#include <cmath>
#include <vector>
#include <climits>
#include "info.h"
#include "constants.h"
#include "levels.h"
#include <iostream>
#include <algorithm>
using namespace std;



Grid::Grid(int startLevel, int seed, Observer<Info> *ob, std::string scriptFile): startLevel{startLevel}, ob{ob} {
	theLevel = std::make_unique<Level0>(this, seed, scriptFile);
	// theLevel = new Level0(this, seed, scriptFile);
	while(theLevel->getLevel() < startLevel) {
		std::unique_ptr<Level> temp(theLevel->levelUp());
		std::swap (theLevel, temp);
		// theLevel = theLevel->levelUp();
	}
	theLevel->setCounter(-2);
	theScore = std::make_unique<Score>();
	td = std::make_unique<TextDisplay>();
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
			c.attach(td.get());
			if(ob) c.attach(ob);
			row.emplace_back(c);
		}
		// adds each row to the beginning so the bottom left is the ORIGIN (0,0)
		// that is, the first row created is the last row of the vector of rows
		theGrid.insert(theGrid.begin(), row);
	}
	// theGrid = res; (TODO)
	std::shared_ptr<Block> temp = theLevel->createBlock();
	std::swap(currentBlock, temp);
	currentBlock->setGridPointer(this);
	currentBlock->moveTo(constants::MAX_ROW, constants::MIN_COL);
	updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING, true);
	
	temp = theLevel->createBlock();
	std::swap(nextBlock, temp);
	nextBlock->setGridPointer(this);
	
	updateDisplays();
}


void Grid::updateDisplays() {
	td->update(theLevel->getLevel(), theScore->getCurrentScore(), theScore->getHighScore());
	if(ob) {
		ob->clearNext();
		ob->update(theLevel->getLevel(), theScore->getCurrentScore(), theScore->getHighScore());
		for (auto &c : nextBlock->getBlockCells()) {
			c.setState(StateType::NEXT);
			c.attach(ob);
			c.notifyObservers();
		}
	}
	
}

// the game is over if the block to be played overlaps a piece that's set
bool Grid::isOver() {
	for (auto &c : currentBlock->getBlockCells()) {
		if (theGrid[constants::GRID_HEIGHT - 1 - c.getInfo().row][c.getInfo().col].getInfo().state 
			== StateType::STATIC) return true;
	}
	return false;

}

// Checks if the row is filled
bool Grid::isFilled(std::vector<Cell> row) {
	for (auto &c : row) {
		if (c.getInfo().state != StateType::STATIC) return false;
	}
	return true;
}


int Grid::countCompleteLines() {
	int rowsToDelete = 0;
	for (int i = theGrid.size() - 1; i >= 0; i--) {
		if (isFilled(theGrid[i])) {
			rowsToDelete++;
		}
	} 
	return rowsToDelete;
}

// higher the value, the more smooth it is (i.e. lower standard deviation)
double Grid::calculateSmoothness() {
	std::vector<int> heights = getHeights();
	double stdHeights = getStandardDeviationHeights(heights);
	return stdHeights;

}

// higher if lessl holes
double Grid::calculateDensity() {
	return 1/ (1 + countHoles());
}


double Grid::getAverageHeights(std::vector<int> v) {      
	double sum = 0;
	for(size_t i = 0;i<v.size();i++) {
		sum+=v[i];

	}
	return sum/v.size();
}

double Grid::getStandardDeviationHeights(std::vector<int> v) {
	double ave = getAverageHeights(v);
	double E=0;
	for(size_t i=0;i<v.size();i++) {
		E += (static_cast<double>(v[i]) - ave) * (static_cast<double>(v[i]) - ave);
	}
	return 1/(E + 1);
}

int Grid::getBumpiness() {
	std::vector<int> heights = getHeights();
	int bumpiness = 0;
	for (int i = 0; i < constants::GRID_WIDTH; i++) {
		bumpiness += abs(heights[i]-heights[i+1]);
	}
	return bumpiness;
}

std::vector<int> Grid::getHeights() {
	std::vector<int> heights(11, 0);
	for (int row = constants::MAX_ROW; row >= constants::MIN_ROW; row--) {
		for ( int col = constants::MIN_COL; col < constants::MAX_COL; col++) {

				// record the index of the highest static block
				// if no height is there, the height is zero
			if (theGrid[constants::GRID_HEIGHT - 1 - row][col].getInfo().state == StateType::STATIC) {
				if (row + 1 > heights[col]) {
					heights[col] = row + 1;
				}
			}
		}
	}

	return heights;
}

void Grid::moveTo(int bottomLeftRow, int bottomLeftCol, std::shared_ptr<Block> &b) {
	int oldBottomLeftRow = b->getBottomLeftRow();
	int oldBottomLeftCol = b->getBottomLeftCol();
	int deltaRow = bottomLeftRow - oldBottomLeftRow;
	int deltaCol = bottomLeftCol - oldBottomLeftCol;

	for (auto &c : b->getBlockCells()) {
		c.setCoords(c.getInfo().row + deltaRow, c.getInfo().col + deltaCol);

	}

}


void Grid::updateCells(std::shared_ptr<Block> &b, BlockType blocktype, StateType s, bool shouldNotify) {

	//Removes hintBlock
	if (hintBlock.get() != nullptr && blocktype != BlockType::HINT) {
		for (auto &c: hintBlock->getBlockCells()) {
			theGrid[constants::GRID_HEIGHT - 1 - c.getInfo().row][c.getInfo().col].setBlock(BlockType::NONE);
			theGrid[constants::GRID_HEIGHT - 1  - c.getInfo().row][c.getInfo().col].notifyObservers();
		}
		hintBlock = nullptr;

	}
	for (auto &c : b->getBlockCells()) {
		theGrid[constants::GRID_HEIGHT - 1  - c.getInfo().row][c.getInfo().col].setState(s);
		theGrid[17 - c.getInfo().row][c.getInfo().col].setBlock(blocktype);
		if (shouldNotify) theGrid[17 - c.getInfo().row][c.getInfo().col].notifyObservers();
	}

}



void notifyRow(std::vector<Cell> & row) {
	for (auto &c : row) {
		c.notifyObservers();
	}

}


void Grid::deleteRow() {
	vector<size_t> deletedRows;

	for (int i = theGrid.size() - 1; i >= 0; i--) {
		if (isFilled(theGrid[i])) {
			//(TODO) code a notify all cels function
			deletedRows.emplace_back(17-i);
			theGrid.erase(theGrid.begin() + i);
			
			//Best Hack
			//(TODO) find a btter way
			if(getLevel()==4) {
				theLevel->restart();
			}
		}
	}

	

	std::reverse(deletedRows.begin(),deletedRows.end());
	//Update whole grid if row is deleted
	if(deletedRows.size()>0) {
		for (int i = theGrid.size() - 1; i >= 0; i--) {
			for (auto &c: theGrid[i]) {
				if(c.getInfo().row < deletedRows[deletedRows.size()-1]) continue;
				for(size_t r:deletedRows) {
					if(c.getInfo().row >= r)
						c.setCoords(c.getInfo().row - 1, c.getInfo().col);
				}
				c.notifyObservers();
			}
		}
		//Recreate Rows
		for (int i = deletedRows.size() - 1; i >= 0; i--) {
			std::vector<Cell> row;
			for (int j = 0; j < 11; j++) {
				Info info;
				info.row = 17 - i;
				info.col = j;
				info.state = StateType::NONE;
				info.block = BlockType::NONE;
				Cell c = Cell{info};
				c.attach(td.get());
				if(ob) c.attach(ob);
				c.notifyObservers();
				row.emplace_back(c);
			}
			theGrid.insert(theGrid.begin(), row);
		}

//	Delete Cells from Block if in deleted row
//	Decrement cell.row in each block
/**		for (auto &b : setBlocks) {
	 		cout << "BEFORE the size of the cells of this set block are" << b->getBlockCells().size() << endl;
	 	}
cout << setBlocks.size() << endl; **/


	 // iterate through each block pointer
		for (int j = setBlocks.size() - 1 ; j >= 0; j--) {
	 	// iterate through each block's cells
	 	// removes cells that are out of bounds, or sets them to the new location

			setBlocks[j]->updateSetCells(deletedRows);

			if (setBlocks[j]->getBlockCells().size() == 0) {
				theScore->addToCurrentScore(pow((setBlocks[j]->getLevel() + 1), 2));
				// delete setBlocks[j];
				setBlocks.erase(setBlocks.begin() + j);
			}

		}

		theScore->addToCurrentScore(pow(theLevel->getLevel() + deletedRows.size(), 2));
	}
}
/**
bool Grid::isValidMove(void (*f)(int), int mult) {

	std::unique_ptr<Block>  cpy = currentBlock->clone();
	cpy.setGridPointer(this);
	while (mult > 0) {
		f(1);
		mult--;
	}

	for (auto &cell: cpy->getBlockCells()) {
		int newrow = cell.getInfo().row;
		int newcol = cell.getInfo().col;
		if ((!(newcol >= 0 && newcol < 11 && newrow >= 0)) || 
			(theGrid[17 - cell.getInfo().row][cell.getInfo().row].getInfo().state == StateType::STATIC)) {
			cout << "INVALID MOVE!" << endl;
			return false;
		}
	
	}
	return true;	
} **/

//For other blocks
bool Grid::isValidMove(std::shared_ptr<Block> &block, int colshift, int rowshift) {
	for (auto &cell: block->getBlockCells()) {
		int newrow = cell.getInfo().row + rowshift;
	//	cout << cell.getInfo().row << "was old row and is now " << newrow << endl;
		int newcol = cell.getInfo().col + colshift;
		

		if ((!(newcol >= 0 && newcol < 11 && newrow >= 0)) || 
			(theGrid[17 - newrow][newcol].getInfo().state == StateType::STATIC)) {
			cout << "INVALID MOVE!" << endl;
		return false;
	}
	
}
return true;	
}

//Default for currentBlock
bool Grid::isValidMove(int colshift, int rowshift) {
	return isValidMove(currentBlock, colshift, rowshift);
}

void Grid::deleteCurrentBlock() {
	// (TODO) refector into currentblock code
	for (size_t i = 0; i < currentBlock->getBlockCells().size(); i++) {
		int row = currentBlock->getBlockCells()[i].getInfo().row;
		int col = currentBlock->getBlockCells()[i].getInfo().col;
		theGrid[17 - row][col].setBlock(BlockType::NONE);
		theGrid[17 - row][col].setState(StateType::NONE);
		theGrid[17 - row][col].notifyObservers();
	}
}





void Grid::left(int x) {
	deleteCurrentBlock();
	// check if valid move
	// update the current block's cells
	int shift = 0;
	while (shift < x) {
		if (isValidMove(-1, 0)) {
			currentBlock->left();
		} else {
			break;
		}
		shift++;
	}
	updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING, true);

	if (currentBlock->isBlockHeavy()) down(1);
	//playBlock(currentBlock;


}

void Grid::right(int x) {
	deleteCurrentBlock();
	int shift = 0;
	while (shift < x) {
		if (isValidMove(1, 0)) {
			currentBlock->right();
		} else {
			break;
		}
		shift++;
	}
updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING, true);

	if(currentBlock->isBlockHeavy()) down(1);
	//playBlock(currentBlock;

}
void Grid::down(int x) {
	deleteCurrentBlock();
	int shift = 0;
	if(currentBlock->isBlockHeavy()) shift++;
	while (shift < x) {
		if (isValidMove( 0, -1)) {
			currentBlock->down();
			// cout <<"YES VALID" << endl;
		} else {
			break;
		}
		shift++;
	}
	
	if(currentBlock->isBlockHeavy()) {
		if (isValidMove( 0, -1)) {
			currentBlock->down();
		}
		else {
			drop(1);
		}
	}	

updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING, true);

}

void Grid::rotateCW(int x) {
	deleteCurrentBlock();

	currentBlock->clockwise(x);

	updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING, true);

	if(currentBlock->isBlockHeavy()) down(1);

}




void Grid::drop(int x) {

	while (x > 0) {
		deleteCurrentBlock();
		while (isValidMove(0, -1)) {
			currentBlock->down();
		}

		updateCells(currentBlock, currentBlock->getBlockType(), StateType::STATIC, true);

		setBlocks.emplace_back(currentBlock);



		// x--;

	//	delete currentBlock; // this is casuing the pointers in update CElls to be wacky
	/**				for (auto &b : setBlocks) {
		for (auto &c : b->getBlockCells()) {
			cout << "HELP ME" << c.getInfo().row << endl;
		}
	} **/

		deleteRow();
		currentBlock = std::move(nextBlock);
		currentBlock->setGridPointer(this);
		currentBlock->moveTo(14,0);
		if(!isOver())
			updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING, true);




		//Makes next block
		std::shared_ptr<Block> temp = theLevel->createBlock();
		std::swap(nextBlock, temp);
		nextBlock->setGridPointer(this);

		updateDisplays();
		x--;

	}
}

void Grid::restart() {
	setBlocks.clear();

	//Go back to level startLevel
	while(getLevel()>startLevel) {
		std::unique_ptr<Level> temp(theLevel->levelDown());
		std::swap (theLevel, temp);
	}
	while(getLevel()<startLevel) {
		std::unique_ptr<Level> temp(theLevel->levelUp());
		std::swap (theLevel, temp);
	}
	theLevel->restart();
	theLevel->setCounter(-2);
	
	theScore->setCurrentScore(0);  
	td->clear();
	if(ob) ob->clear();
	initGrid(); 
	updateDisplays();

}

void Grid::rotateCCW(int x) {
	deleteCurrentBlock();
	while (x > 0) {
		currentBlock->counterclockwise(x);
		x--;

	}
	updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING, true);

	if(currentBlock->isBlockHeavy()) down(1);
}
void Grid::levelUp(int x) {
	for(int i=0; i<x; i++) {
		std::unique_ptr<Level> temp(theLevel->levelUp());
		std::swap (theLevel, temp);
	}
	updateDisplays();
}

void Grid::levelDown(int x) {
	for(int i=0; i<x; i++) {
		std::unique_ptr<Level> temp(theLevel->levelDown());
		std::swap (theLevel, temp);
	}
	updateDisplays();
}

void Grid::random(bool flag) {
	theLevel->setRandom(flag);
}

void Grid::setRandomFile(std::string file) {
	theLevel->setFile(file);
}

int Grid::countHoles() {
	std::vector<int> heights = getHeights();
	int numHoles = 0; 
	// for all the cells below the highest cell
	
	for (size_t i = 0; i < heights.size(); i++) {
		for (int row = 0; row < heights[i] - 1; row++) {
			if (theGrid[17 - row][i].getInfo().state == StateType::NONE) {
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

int Grid::countNumCellsOnGround(){
	int numCells = 0;
	for (auto &c : theGrid[17]) {
		if (c.getInfo().state == StateType::STATIC) {
			numCells++;
		}
	}
	return numCells;
}

int Grid::countNumCellsOnWall(){
	int numCells = 0;
	for (auto &row : theGrid) {
		if (row[0].getInfo().state == StateType::STATIC) {
			numCells++;
		}
		if (row[10].getInfo().state == StateType::STATIC) {
			numCells++;
		}
	}
	return numCells;
}

// the higher the priority, the better the move
// algorithm arbitrarily constructed and can be adjusted
double Grid::calculatePriority() {
	std::vector<int> heights = getHeights();
	return -sqrt((getBumpiness())) - (2.5 * countHoles()) + (countCompleteLines() * 3.5) 
	+  countNumCellsOnGround() + 0.5 * countNumCellsOnWall();
}



void Grid::hint() {

	vector<Cell> hintCells;
	// store the original position of the block when hint
	// was called so that the block in play can be moved back
	int oldBottomLeftRow = currentBlock->getBottomLeftRow();
	int oldBottomLeftCol = currentBlock->getBottomLeftCol();
	HintInfo best{0,0,0,INT_MIN};

	// for eah dir 1 & -1 (each deemed a trial), to determine all possible moves
	// to the right and to the left 
	int dir = 1;
	bool hasLeft = false;

	// for each direction
	for (int trial = 0; trial < 2; trial++) {

		// for each rotation
		for (int i = 0; i < 4; i++) {
			int horizontal = 0;
			while (isValidMove(dir * horizontal, 0)) {
				// play every possible horizontal move
				for (int i = 0; i < horizontal; i++) {
					// depending on the hasLeft flag, move right/left
					if (hasLeft == false) currentBlock->right(1);
					else currentBlock->left(1);
				}
				// for every horizontal move, move all the way down
				while (isValidMove(0, -1)) {
					currentBlock->down(1);
				}

				// temporarily set the block and calculate the priority score
				updateCells(currentBlock, currentBlock->getBlockType(), StateType::STATIC, false);

				double tempPriority = calculatePriority();

				if (tempPriority > best.priority) {
					best.priority = tempPriority;
					best.numRotations = i;
					best.bottomLeftCol = currentBlock->getBottomLeftCol();
					best.bottomLeftRow = currentBlock->getBottomLeftRow();
				}

				// unset the block and move to original position for the next
				// simulation of moves
					updateCells(currentBlock, BlockType::NONE, StateType::NONE, false);

				currentBlock->moveTo(oldBottomLeftRow,oldBottomLeftCol);
				horizontal++;

			}
			currentBlock->clockwise(1);

		}

		// update the flag 
		if (hasLeft == false) {
			dir = -1;
			hasLeft = true;
		}
	}

	// one all the possible sequence of moves have been played,
	// move the block to the original 
	updateCells(currentBlock, BlockType::NONE, StateType::NONE, false);
	currentBlock->moveTo(oldBottomLeftRow,oldBottomLeftCol);
	updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING, true);
	hintBlock = currentBlock->clone();

	hintBlock->setGridPointer(this);
	int numRotations = best.numRotations;
	int newBottomLeftCol = best.bottomLeftCol;
	int newBottomLeftRow = best.bottomLeftRow;
	hintBlock->clockwise(numRotations);
	hintBlock->moveTo(newBottomLeftRow, newBottomLeftCol);

	// set the appropriate blocks 
	updateCells(hintBlock, BlockType::HINT, StateType::NONE, true);



}


std::shared_ptr<Block>  Grid::getNextBlock() {
	return nextBlock;
}


int Grid::getLevel() {
	return theLevel->getLevel();
}


// replaces the current block at play
void Grid::replaceBlock(char type) {

	std::shared_ptr<Block> temp = currentBlock->clone();
	int col = currentBlock->getBottomLeftCol();
	int row = currentBlock->getBottomLeftRow();
	deleteCurrentBlock();
	
	
	currentBlock = theLevel->getBlock(type, currentBlock->getLevel(), currentBlock->isBlockHeavy());
	currentBlock->setGridPointer(this);
	if(isValidMove(col, row)) {
		currentBlock->moveTo(row, col);
		updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING, true);

	}
	else {
		std::swap(currentBlock, temp);
		updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING,  true);

	}
}

// drops a block all the way down to the lowest valid coordinate
// used for Dot Block
void Grid::dropBlock(std::shared_ptr<Block> block, int col) {
	block->setGridPointer(this);
	block->moveTo(17,col);
	while (isValidMove(block, 0, -1)) {
		block->down();
	}

	updateCells(block, block->getBlockType(), StateType::STATIC, true);
	setBlocks.emplace_back(std::move(block));

	deleteRow();
	updateDisplays();
}


std::ostream &operator<<(std::ostream &out, Grid &grid) {
	out << *(grid.td.get());
	out << grid.getNextBlock().get();
	return out;
}




