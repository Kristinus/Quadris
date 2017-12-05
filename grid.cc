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


struct HintInfo {
	int bottomLeftRow;
	int bottomLeftCol;
	int numRotations;
	double priority;
	HintInfo(int blr, int blc, int nr, double p): bottomLeftRow{blr}, bottomLeftCol{blc},
	numRotations{nr}, priority{p} {

	}

};


Grid::Grid(int startLevel, int seed, Observer<Info> *ob, std::string scriptFile): startLevel{startLevel}, ob{ob} {
	theLevel = std::make_unique<Level0>(this, seed, scriptFile);
	while(theLevel->getLevel() < startLevel) {
		std::unique_ptr<Level> temp(theLevel->levelUp());
		std::swap (theLevel, temp);
	}
	theLevel->setCounter(-2);
	theScore = std::make_unique<Score>();
	td = std::make_unique<TextDisplay>();
	initGrid();
}


std::vector<std::vector<Cell>> Grid::getGridCells() const {
	return theGrid;
}


void Grid::initGrid() {
	theGrid.clear();
	
	for (int i = constants::MIN_ROW; i < constants::GRID_HEIGHT; i++) {
		std::vector<Cell> row;
		for (int j = constants::MIN_COL; j < constants::MAX_COL; j++) {
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

	currentBlock = theLevel->createBlock();
	currentBlock->moveTo(constants::MAX_ROW, constants::MIN_COL);
	updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING, true);
	nextBlock = theLevel->createBlock();
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
		if(holdBlock) {
			for (auto &c : holdBlock->getBlockCells()) {
				c.setState(StateType::HOLD);
				c.attach(ob);
				c.notifyObservers();
			}
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

	for (int i = constants::GRID_HEIGHT - 1; i >= constants::MIN_ROW; i--) {
		if (isFilled(theGrid[i])) {
			rowsToDelete++;
		}
	} 
	return rowsToDelete;
}


int Grid::getBumpiness(const std::vector<int> &heights) {
	int bumpiness = 0;
	for (int i = constants::MIN_COL; i < constants::GRID_WIDTH; i++) {
		bumpiness += abs(heights[i]-heights[i+1]);
	}
	return bumpiness;
}


std::vector<int> Grid::getHeights() {
	std::vector<int> heights(constants::MAX_COL, 0);
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


void Grid::updateCells(std::shared_ptr<Block> &b, BlockType blocktype, StateType s, bool shouldNotify) {

	//Removes hintBlock after one move is played
	if (hintBlock.get() != nullptr && blocktype != BlockType::HINT) {
		for (auto &c: hintBlock->getBlockCells()) {
			theGrid[constants::GRID_HEIGHT - 1 - c.getInfo().row][c.getInfo().col].setBlock(BlockType::NONE);
			theGrid[constants::GRID_HEIGHT - 1  - c.getInfo().row][c.getInfo().col].notifyObservers();
		}
		hintBlock = nullptr;
	}

	// updates the grid's cell states and block types
	// if Block and statetype are none, this essentially deletes the block from the grid
	for (auto &c : b->getBlockCells()) {
		theGrid[constants::GRID_HEIGHT - 1  - c.getInfo().row][c.getInfo().col].setState(s);
		theGrid[constants::GRID_HEIGHT - 1 - c.getInfo().row][c.getInfo().col].setBlock(blocktype);
		if (shouldNotify) theGrid[constants::GRID_HEIGHT - 1 - c.getInfo().row][c.getInfo().col].notifyObservers();
	}

}


// deleteRow is called every time drop is called
// checks for rows to be deleted, deletes them, and updates the grid
void Grid::deleteRow() {
	vector<size_t> deletedRows;
	for (int i = theGrid.size() - 1; i >= constants::MIN_ROW; i--) {
		if (isFilled(theGrid[i])) {
			deletedRows.emplace_back(constants::GRID_HEIGHT - 1 - i);
			theGrid.erase(theGrid.begin() + i);
			if (getLevel() == 4) {
				theLevel->restart();
			}
		}
	}

	std::reverse(deletedRows.begin(),deletedRows.end());
	//Update whole grid if row is deleted
	if(deletedRows.size() > 0) {
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
			for (int j = constants::MIN_COL; j < constants::MAX_COL; j++) {
				Info info;
				info.row = constants::GRID_HEIGHT - 1 - i;
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


bool Grid::isValidMove(std::shared_ptr<Block> &block, int colshift, int rowshift) {
	for (auto &cell: block->getBlockCells()) {
		int newrow = cell.getInfo().row + rowshift;
		int newcol = cell.getInfo().col + colshift;

		if ((!(newcol >= constants::MIN_COL && newcol < constants::MAX_COL && newrow >= constants::MIN_ROW)) || 
			(theGrid[constants::GRID_HEIGHT - 1 - newrow][newcol].getInfo().state == StateType::STATIC)) {
		return false;
	}
	
	}
	return true;	
}


//Default for currentBlock
bool Grid::isValidMove(int colshift, int rowshift) {
	return isValidMove(currentBlock, colshift, rowshift);
}


void Grid::left(int x) {
	updateCells(currentBlock, BlockType::NONE, StateType::NONE, true);

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

}


void Grid::right(int x) {
	updateCells(currentBlock, BlockType::NONE, StateType::NONE, true);
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

}
void Grid::down(int x) {
	updateCells(currentBlock, BlockType::NONE, StateType::NONE, true);

	int shift = 0;
	if(currentBlock->isBlockHeavy()) shift++;
	while (shift < x) {
		if (isValidMove( 0, -1)) {
			currentBlock->down();
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
	updateCells(currentBlock, BlockType::NONE, StateType::NONE, true);
	currentBlock->clockwise(this, x);
	updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING, true);
	if(currentBlock->isBlockHeavy()) down(1);

}


void Grid::drop(int x) {

	while (x > 0) {
		updateCells(currentBlock, BlockType::NONE, StateType::NONE, true);

		while (isValidMove(0, -1)) {
			currentBlock->down();
		}

		updateCells(currentBlock, currentBlock->getBlockType(), StateType::STATIC, true);
		setBlocks.emplace_back(currentBlock);
		deleteRow();
		currentBlock = std::move(nextBlock);
		currentBlock->moveTo(constants::MAX_ROW,constants::MIN_COL);
		if(!isOver()) {
			updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING, true);
		}

		//Makes next block
		std::shared_ptr<Block> temp = theLevel->createBlock();
		std::swap(nextBlock, temp);
		updateDisplays();
		x--;
	}
}

void Grid::restart() {
	setBlocks.clear();

	//Go back to level startLevel
	if(startLevel < getLevel()) {
		levelDown(getLevel()-startLevel);
	}
	else{
		levelUp(startLevel-getLevel());
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
	updateCells(currentBlock, BlockType::NONE, StateType::NONE, true);

	while (x > 0) {
		currentBlock->counterclockwise(this, x);
		x--;

	}

	updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING, true);
	if(currentBlock->isBlockHeavy()) down(1);
}


void Grid::levelUp(int x) {
	for(int i = 0; i < x; i++) {
		std::unique_ptr<Level> temp(theLevel->levelUp());
		if(theLevel.get()==temp.get())
			temp.release();
		else
			std::swap (theLevel, temp);
	}
	updateDisplays();
}


void Grid::levelDown(int x) {
	for (int i = 0; i < x; i++) {
		std::unique_ptr<Level> temp(theLevel->levelDown());
		if(theLevel.get()==temp.get())
			temp.release();
		else
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


int Grid::countHoles(const std::vector<int> &heights) {
	int numHoles = 0; 
	// for all the cells below the highest cell
	
	for (size_t i = 0; i < heights.size(); i++) {
		for (int row = 0; row < heights[i] - 1; row++) {
			if (theGrid[constants::GRID_HEIGHT - 1 - row][i].getInfo().state == StateType::NONE) {
				numHoles++;
			}
		}
	}
	return numHoles;
}


int Grid::countNumCellsOnGround(){
	int numCells = 0;
	for (auto &c : theGrid[constants::GRID_HEIGHT - 1]) {
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
	return -sqrt((getBumpiness(heights))) - (2.5 * countHoles(heights)) + (countCompleteLines() * 3.5) 
	+  countNumCellsOnGround() + 0.5 * countNumCellsOnWall();
}


void Grid::hint() {

	vector<Cell> hintCells;
	// store the original position of the block when hint
	// was called so that the block in play can be moved back
	int oldBottomLeftRow = currentBlock->getBottomLeftRow();
	int oldBottomLeftCol = currentBlock->getBottomLeftCol();
	HintInfo best{0, 0, 0, INT_MIN};

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
			currentBlock->clockwise(this, 1);

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

	int numRotations = best.numRotations;
	int newBottomLeftCol = best.bottomLeftCol;
	int newBottomLeftRow = best.bottomLeftRow;
	hintBlock->clockwise(this, numRotations);
	hintBlock->moveTo(newBottomLeftRow, newBottomLeftCol);

	// set the appropriate blocks 
	updateCells(hintBlock, BlockType::HINT, StateType::NONE, true);
}

// BONUS FEATURE: save the current block and play the next block
// or swap the current block with the block on hold
void Grid::hold() {
	updateCells(currentBlock, BlockType::NONE, StateType::NONE, true);
	if(holdBlock) {
		int col = currentBlock->getBottomLeftCol();
		int row = currentBlock->getBottomLeftRow();

		if(isValidMove(holdBlock, col, row)) {
			std::swap(currentBlock, holdBlock);
			currentBlock->moveTo(row, col);
			holdBlock->moveTo(constants::MIN_ROW, constants::MIN_COL);
		}
		updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING, true);
	}
	else {
		swap(currentBlock, holdBlock);
		swap(currentBlock, nextBlock);
		currentBlock->moveTo(constants::MAX_ROW, constants::MIN_COL);
		holdBlock->moveTo(constants::MIN_ROW, constants::MIN_COL);
		updateCells(currentBlock, currentBlock->getBlockType(), StateType::MOVING, true);
		nextBlock = theLevel->createBlock();

	}
	updateDisplays();
}


std::shared_ptr<Block>  Grid::getNextBlock() const {
	return nextBlock;
}

std::shared_ptr<Block>  Grid::getHoldBlock() const {
	return holdBlock;
}


int Grid::getLevel() const {
	return theLevel->getLevel();
}


// replaces the current block at play
void Grid::replaceBlock(char type) {
	std::shared_ptr<Block> temp = currentBlock->clone();
	int col = currentBlock->getBottomLeftCol();
	int row = currentBlock->getBottomLeftRow();
	updateCells(currentBlock, BlockType::NONE, StateType::NONE, true);
	currentBlock = theLevel->getBlock(type, currentBlock->getLevel(), currentBlock->isBlockHeavy());
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
	block->moveTo(constants::GRID_HEIGHT - 1,col);
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
	out << "Next:" << std::endl;
	out << grid.getNextBlock().get();
	out << "Hold:" << std::endl;
	if(grid.getHoldBlock())
		out << grid.getHoldBlock().get();
	else	
		out << "(NONE)" << std::endl;
	out << "Input::";
	return out;
}




