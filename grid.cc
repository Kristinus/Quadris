#include "grid.h"
#include "cell.h"
#include <vector>


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
			//c.attach(td)
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

}

void Grid::left() {

}
void Grid::right() {

}
void Grid::down() {

}
void Grid::drop() {

}
void Grid::restart() {

}
void Grid::rotateCW() {

}
void Grid::rotateCCW() {

}
void Grid::levelUp() {

}
void Grid::levelDown(){

}
void Grid::random(){

}
void Grid::hint(){

}


