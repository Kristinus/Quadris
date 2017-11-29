#include "grid.h"
#include <cmath>
#include "cell.h"
#include <vector>

Grid::Grid():td{new TextDisplay()} {
}


void Grid::initGrid() {
	theGrid.clear();
	//td = new TextDisplay(n);
	

	for (int i = 0; i < 18; i++) {
		std::vector<Cell> row;
		for (int j = 0; j < 11; j++) {
			Info info;
			info.row = i;
			info.col = j;
			info.block = BlockType::None;
			info.state = StateType::None;
			Cell c = Cell(info);
			c.parentBlock = nullptr;
			c.attach(td)
			row.emplace_back(Cell(info));
		}
		// adds each row to the beginning so the bottom left is the ORIGIN (0,0)
		theGrid.insert(theGrid.begin());
	}
	theGrid = res;

}

bool Grid::isOver() {
	// if the piece in play cannot be played

}

//Checks if the row is filled
bool isFilled(std::vector row) {
	for (auto c : row) {
		if (c.info.state != StateType::STATIC) return false;
	}
	return true;
}

void Grid::deleteRow() {
	int rowsToDelete = 0;
	for (int i = theGrid.size() - 1; i >= 0; i--) {
		if (isFilled(theGrid[i])) {
			theGrid.erase(begin() + i);
			rowsToDelete++;
		}
	}

	for (auto row : theGrid) {
		for (auto c: row) {
			c.info.row -= rowsToDelete;
		}
	}

	//Recreate Rows
	for (int i = rowsToDelete - 1; i >= 0; i++) {
		vector<Cell> row;
		for (int j = 0; j < 11; j++) {
			Info info;
			info.row = 17 - i;
			info.col = j;
			info.state = StateType::None;
			info.block = BlockType::None;
			Cell c = Cell{info};
			row.emplace_back(c)
		}
		theGrid.insert(theGrid.begin(), row);
	}

	// iterate through each block pointer
	for (int i = setBlocks.size() - 1; i >= 0; i--) {
		// iterate through each block's cells
		for (int i = block->cells.size() - 1; i >= 0; i--) {
			// if the row goes out of bounds, then erase the cell
			if (block->cells.info.row - rowsToDelete < 0) {
				block->cells.erase(block->cells.begin() + i);
			} else {
				// decrement each setBlock's 
				block->cells.info.row -= rowsToDelete;
			}

			// if all the cells of blocks  have been removed, then delete the block from set blocks and calculate the score
			if (block->cells.size() == 0) {
				int points = pow((setBlocks[i]->level + 1),2);
				score += points;
				delete setBlocks[i];
				setBlocks.erase(setBlocks.begin() + i);
			}

		}
	
	}

}

bool isValidMove(vector<Cells> theCells, int offsetX, int offsetY) {
	for (auto cell: theCells) {
		int newX = cell.info.x + offsetX;
		int newY = cell.info.y + offsetY;

		if !((newX >= 0 && (newX <= 11) && (newY >= 0)
			&& theGrid[newX][newY].info.state != StateType::STATIC)) {
			return false;
		}
	}
	return true;
}

// updates each cell of setblocks by the offset, depending on left, right, down
void updateCurblockIndices(vector<Cells> &theCells, int offsetX, int offsetY) {
	for (auto &cell: theCells) {
		cell.info.row += offsetX;
		cell.info.col += offsetY;
	}
}

void Grid::left(int x) {
	// check if valid move
	// update the current block's cells
	int shift = 0;
	while (shift < x) {
		if (!isValidMove(currentBlock->cells, -1, 0)) {
			break;
		}
		shift++;
	}

	updateCurblockIndices(currentBlock->cells, -shift, 0);

}

void Grid::right(int x) {

	int shift = 0;
	while (shift < x) {
		if (!isValidMove(currentBlock->cells, 1, 0)) {
			break;
		}
		shift++;
	}

	updateCurblockIndices(currentBlock->cells, shift, 0);

}
void Grid::down(int x) {
	int shift = 0;
	while (shift < x) {
		if (!isValidMove(currentBlock->cells, 0, -1)) {
			break;
		}
		shift++;
	}
	updateCurblockIndices(currentBlock->cells, 0, -shift);

}

void setBlock(Block *curBlock) {
	for (auto cell : currentBlock->cells) {
		theGrid[cell.info.row][cell.info.col].setState(StateType::STATIC);
	}
	setBlocks.emplace_back(currentBlock);
}

void Grid::drop(int x) {
	int shift = 0;
	while (isValidMove(currentBlock->cells, 0, -shift)) {
		updateCurblockIndices(currentBlock->cells, 0, -1);
	}
	setBlock(currentBlock);
	//currentBlock = nextBlock;
	//nextBlock = theLevel->createBlock();

}

void Grid::restart() {

}
void Grid::rotateCW(int x) {

}
void Grid::rotateCCW(int x) {

}
void Grid::levelUp(int x) {

}
void Grid::levelDown(int x) {

}
void Grid::random() {

}
void Grid::hint() {

}


