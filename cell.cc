#include "cell.h"
#include "info.h"


// recall info holds row, col, state, and blcoktype

Cell::Cell(Info &info): info{info} {}

void Cell::setBlock(BlockType block) {
	info.block = block;
   
}

void Cell::setCoords(size_t r, size_t c) {
	info.row = r;
	info.col = c;
}

void Cell::setState(StateType state) {
	info.state = state;
}

Info Cell::getInfo() const {
	return info;
} 


