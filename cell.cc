#include "cell.h"
#include "info.h"

Cell::Cell(Info &info): info{info} {}


void Cell::setBlock(BlockType block) {
	info.block = block;   
}


void Cell::setCoords(unsigned int r, unsigned int c) {
	info.row = r;
	info.col = c;
}


void Cell::moveDown(unsigned int x) {
	info.row -= x;
}


void Cell::setState(StateType state) {
	info.state = state;
}


Info Cell::getInfo() const {
	return info;
} 

