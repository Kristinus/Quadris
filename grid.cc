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


}
void Grid::deleteRow() {

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


