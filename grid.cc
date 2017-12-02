#include "grid.h"
#include <cmath>
#include "cell.h"
#include "blocks.h"
#include <vector>
#include "info.h"
#include "levels.h"
#include <iostream>
using namespace std;


Grid::Grid(int seed, Observer<Info> *ob, std::string scriptFile): ob{ob} {
// NEED TO FIGURE THIS SHIT OUT
	theLevel = new Level0(seed, scriptFile);
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
			if(ob) c.attach(ob);
			row.emplace_back(c);
		}
		// adds each row to the beginning so the bottom left is the ORIGIN (0,0)
		theGrid.insert(theGrid.begin(), row);
	}
	// theGrid = res; (TODO)

	currentBlock = theLevel->createBlock();
	currentBlock->setGridPointer(this);
	// for (auto c: currentBlock->getBlockCells()) {
	// 	cout << "(" << c.getInfo().row << "," << c.getInfo().col << ")" << endl;
	// }
	currentBlock->moveTo(14,0);
	// for (auto c: currentBlock->getBlockCells()) {
	// 	cout << "(" << c.getInfo().row << "," << c.getInfo().col << ")" << endl;
	// }
	updateCells(currentBlock, StateType::NONE);

	nextBlock = theLevel->createBlock();
	nextBlock->setGridPointer(this);
	if(ob) nextBlock->displayNext(ob);

}

bool Grid::isCurrentBlockOverlap() {
	for (auto &c : currentBlock->getBlockCells()) {
		if (theGrid[17 - c.getInfo().row][c.getInfo().col].getInfo().state == StateType::STATIC) return true;
	}
	return false;
}

bool Grid::isOver() {
	return isCurrentBlockOverlap();

	// if the piece in play cannot be played

	// if (theScore->getCurrentScore > theScore->getHighScore) {
	// 	theScore->setHighScore(theScore->getCurrentScore);
	// }

}

//Checks if the row is filled
bool Grid::isFilled(std::vector<Cell> row) {
	for (auto &c : row) {
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
		double sum=0;
       for(int i=0;i<v.size();i++) {
			sum+=v[i];

       }


	return sum/v.size();
}
//DEVIATION
double Grid::getStandardDeviationHeights(std::vector<int> v) {
		double ave = getAverageHeights(v);
       double E=0;
       for( int i=0;i<v.size();i++) {
       	cout << static_cast<double>(v[i]) << endl;
       	E += (static_cast<double>(v[i]) - ave) * (static_cast<double>(v[i]) - ave);
}
       return 1/(E + 1);

       // the higher your scre the mo
       //return sqrt(1/v.size()*E);
}

std::vector<int> Grid::getHeights() {
	std::vector<int> heights(11);
	cout << "hi1" << endl;
	cout << theGrid[0][6].getInfo().row;
	for ( int row = 17; row >= 0; row--) {
			for ( int col = 0; col < 11; col++) {
				// record the index of the highest static block...if no block is there... height is 0
				if (theGrid[17 - row][col].getInfo().state == StateType::STATIC) {
					cout << row << "|" << col << endl;
					if (row + 1 > heights[col]) {
						heights[col] = row;
				}
			}
		}
	}

	for (auto &c : heights) {
		c++;
	}
	cout <<"hi2"<< endl;

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

}

// update cell Grid
void Grid::updateCells(Block *b, StateType s) {
	b->setBlockCellStates(s);
	for (auto &c : b->getBlockCells()) {
		c.setBlock(b->getBlockType()); // is this necessary
		theGrid[17 - c.getInfo().row][c.getInfo().col].setBlock(b->getBlockType());
		theGrid[17 - c.getInfo().row][c.getInfo().col].setState(s);
		theGrid[17 - c.getInfo().row][c.getInfo().col].notifyObservers();
	}

	if (s == StateType::STATIC) {
		setBlocks.emplace_back(b);
	}

}

void Grid::updateCells(Block *b) {
	for (auto &c : b->getBlockCells()) {
		c.setBlock(b->getBlockType()); // is this necessary
		theGrid[17 - c.getInfo().row][c.getInfo().col].setBlock(b->getBlockType());
		theGrid[17 - c.getInfo().row][c.getInfo().col].notifyObservers();
	}

}

void notifyRow(std::vector<Cell> & row) {
	for (auto &c : row) {
		c.notifyObservers();
	}

}


void Grid::deleteRow() {
	int rowsToDelete = 0;
	int lowerRow=0;
	for (int i = theGrid.size() - 1; i >= 0; i--) {
		if (isFilled(theGrid[i])) {
			//(TODO) code a notify all cels function
			lowerRow = i;
			for (auto &c : theGrid[i]) {
				c.setState(StateType::NONE);
				c.setBlock(BlockType::NONE);
				//notifyRow(the);

			}

			theGrid.erase(theGrid.begin() + i);
			rowsToDelete++;
		}
	}
	//make a notifygrid


	for (int i=0; i<lowerRow; i++) {
		for (auto &c: theGrid[i]) {
			c.setCoords(c.getInfo().row - rowsToDelete, c.getInfo().col);
		}
	}

	//Recreate Rows
	for (int i = rowsToDelete - 1; i >= 0; i--) {
		std::vector<Cell> row;
		for (int j = 0; j < 11; j++) {
			Info info;
			info.row = 17 - i;
			info.col = j;
			info.state = StateType::NONE;
			info.block = BlockType::NONE;
			Cell c = Cell{info};
			c.attach(td);
			if(ob) c.attach(ob);
			row.emplace_back(c);
		}
		theGrid.insert(theGrid.begin(), row);
	}

	//Update whole grid if row is deleted
	if(rowsToDelete>0) {
		for (auto &row : theGrid) {
			for (auto &c: row) {
				c.notifyObservers();
			}
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

	 	setBlocks[j]->updateSetCells(rowsToDelete);

	 	if (setBlocks[j]->getBlockCells().size() == 0) {
	 		theScore->addToCurrentScore(pow((setBlocks[j]->getLevel() + 1), 2));
	 		delete setBlocks[j];
	 		setBlocks.erase(setBlocks.begin() + j);
	 	}
	
	 }

		theScore->addToCurrentScore(pow(theLevel->getLevel() + rowsToDelete, 2));
	}
}

bool Grid::isValidMove(int colshift, int rowshift) {
	for (auto &cell: currentBlock->getBlockCells()) {
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

void Grid::deleteCurrentBlock() {
	// (TODO) refector into currentblock code
	for (int i = 0; i < currentBlock->getBlockCells().size(); i++) {
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
	updateCells(currentBlock);
	if(currentBlock->isBlockHeavy()) down(1);
	//playBlock(currentBlock);


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
	updateCells(currentBlock);
	if(currentBlock->isBlockHeavy()) down(1);
	//playBlock(currentBlock);

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

	updateCells(currentBlock);
	//playBlock(currentBlock);
}

void Grid::rotateCW(int x) {
		deleteCurrentBlock();

	//while (x > 0) {
		currentBlock->clockwise(x);
	//	x--;
	//}

	updateCells(currentBlock);
	if(currentBlock->isBlockHeavy()) down(1);
	//playBlock(currentBlock);

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
		deleteCurrentBlock();
		while (isValidMove(0, -1)) {
			currentBlock->down();
		}

		updateCells(currentBlock, StateType::STATIC);



		// x--;

	//	delete currentBlock; // this is casuing the pointers in update CElls to be wacky
	/**				for (auto &b : setBlocks) {
		for (auto &c : b->getBlockCells()) {
			cout << "HELP ME" << c.getInfo().row << endl;
		}
	} **/
	
		deleteRow();

		currentBlock = nextBlock;
		currentBlock->setGridPointer(this);
		currentBlock->moveTo(14,0);
		updateCells(currentBlock);


		//cout <<"hi";
		nextBlock = theLevel->createBlock();
		nextBlock->setGridPointer(this);
		if(ob)ob->clearNext();
		if(ob) nextBlock->displayNext(ob);
		x--;

	}


	


}

void Grid::restart() {
	for (auto b : setBlocks) {
		delete b;
	}
	setBlocks.clear();

    delete currentBlock;
    delete nextBlock;
    // note: level doesn't change
	td->clear();
	ob->clear();
    initGrid(); 
//     currentBlock = theLevel->createBlock();
// 	currentBlock->setGridPointer(this);
// 	currentBlock->moveTo(14,0);
// 	//updateCells(currentBlock, StateType::MOVING);



//    // playBlock(currentBlock);
//     nextBlock = theLevel->createBlock();
//     nextBlock->setGridPointer(this);



    theScore->setCurrentScore(0);  

}

void Grid::rotateCCW(int x) {
	updateCells(currentBlock, StateType::NONE);
	while (x > 0) {
		currentBlock->counterclockwise(x);
		x--;

	}
	updateCells(currentBlock, StateType::MOVING);
	//playBlock(currentBlock);
	if(currentBlock->isBlockHeavy()) down(1);
}
void Grid::levelUp(int x) {
	for(int i=0; i<x; i++)
		theLevel = theLevel->levelUp();
	if(ob) ob->update();
}

void Grid::levelDown(int x) {
	for(int i=0; i<x; i++)
		theLevel = theLevel->levelDown();
	if(ob) ob->update();
}

void Grid::random(bool flag) {
	theLevel->setRandom(flag);
}

void Grid::setRandomFile(std::string file) {
	theLevel->setFile(file);
}

int Grid::countHoles() {
	std::vector<int> heights = getHeights();
	for (auto i : heights) {
		//cout << "the height is " << i << endl;
	}
	int numHoles = 0; 
	// for all the cells below the highest cell
	
		for (int i = 0; i < heights.size(); i++) {
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

double Grid::calculatePriority() {
	return calculateSmoothness() + countCompleteLines() + calculateDensity();
}



void Grid::hint() {
	vector<Cell> hintCells;
	int oldBottomLeftRow = currentBlock->getBottomLeftRow();
	int oldBottomLeftCol = currentBlock->getBottomLeftCol();


	for (int i = 0; i < 4; i++) {
		HintInfo best{0,0,0,0};
		int horizontal = 0;


		while (isValidMove(horizontal, 0)) {
			currentBlock->right(horizontal);
			while (isValidMove(0, -1)) {
				currentBlock->down(1);
			}
			horizontal++;

		}

		updateCells(currentBlock, StateType::MOVING);


		double tempPriority = calculatePriority();

		if (tempPriority > best.priority) {
			best.priority = tempPriority;
			best.numRotations = 3;
			best.bottomLeftCol = 3;
			best.bottomLeftRow = 2;
		}
		updateCells(currentBlock, StateType::NONE);
		currentBlock->moveTo(oldBottomLeftRow,oldBottomLeftCol);
		currentBlock->clockwise(1);

	//	cout << "smoothness:" << smoothness << " completeLines: " << completeLines << "numHoles: " << numHoles << endl;
		//double priority = (1/ (1+smoothness)) * completeLines * 1/(numHoles+1);
		cout << "the hint we want to give: " << best.bottomLeftCol << " BL" << "with Rotations " << best.numRotations << endl;



	}

		

}
/**
void Grid::hint() {
	cout << "HINT" << endl;

	// MAKE SURE TO RESET HINTINFO
	// RESET THE HINT BLOCK
	// CODE THE MOVE TO HINT INFO WITH ROTATIONS AND TRANSLATIONS

	std::vector<HintInfo> hintInfo;
		cout << "HINT" << endl;


	//Block temp{*currentBlock}; // implement the Copy Ctor
	hintBlock = theLevel->createBlock();
		cout << "HINT" << endl;


	for (unsigned int i = 0; i < 4; i++) {
		try {
			hintBlock->clockwise(i);
		} catch (...) { // rotaetfailexception
			continue;
		}

		int horizontal = 0;
		// make default params to be currenbloc cells
		while (isValidMove(horizontal, 0)) {

			hintBlock->right(horizontal);
			while (isValidMove(0, -1)) {
				hintBlock->down(1);
			}

			// /setBlock(hintBlock);
			double smoothness = calculateSmoothness();
			int completeLines = countCompleteLines();
			int numHoles = countHoles();
			cout << "smoothness:" << smoothness << " completeLines: " << completeLines << "numHoles: " << numHoles << endl;
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
**/
Block * Grid::getNextBlock() {
	return nextBlock;
}

Score *Grid::getScore() {
	return theScore;
}

int Grid::getLevel() {
	return theLevel->getLevel();
}

void Grid::replaceBlock(char type) {
	currentBlock = theLevel->getBlock(type);

	//(TODO) replace current block (move to location)
}

// void Grid::heavyMove() {
// 	if(currentBlock->isBlockHeavy()) down(1);
// }


std::ostream &operator<<(std::ostream &out, Grid &grid) {
	out << *(grid.td);
	return out;
}




