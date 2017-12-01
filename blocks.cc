#include "blocks.h"
#include "info.h"

IBlock::IBlock(bool isHeavy): Block(isHeavy) {
    type = 'I';
    Info i;
    i.row = 0;
    i.col = 0;
    i.state = StateType::NONE;
    i.block = BlockType::I;
    for(int c=0; c<4; c++) {
        i.col = c;
        cells.emplace_back(Cell(i));   
    }
}
// IBlock::IBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// IBlock::IBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

IBlock::~IBlock() {}
BlockType IBlock::getBlockType() {
	return BlockType::I;
}



/*****************************************************************************/

JBlock::JBlock(bool isHeavy): Block(isHeavy) {
    type = 'J';
    Info i;
    i.row = 0;
    i.col = 0;
    i.state = StateType::NONE;
    i.block = BlockType::J;
    cells.emplace_back(Cell(i));
    i.row = 1;
    for(int c=0; c<3; c++) {
        i.col = c;
        cells.emplace_back(Cell(i));   
    }
}
// JBlock::JBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// JBlock::JBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

JBlock::~JBlock() {}
BlockType JBlock::getBlockType() {
	return BlockType::J;
}



/*****************************************************************************/

LBlock::LBlock(bool isHeavy): Block(isHeavy) {
    type = 'L';
    Info i;
    i.row = 0;
    i.col = 2;
    i.state = StateType::NONE;
    i.block = BlockType::L;
    cells.emplace_back(Cell(i));
    i.row = 1;
    i.col = 0;
    for(int c = 0;c < 3; c++) {
        i.col = c;
        cells.emplace_back(Cell(i));
    }

}
// LBlock::LBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// LBlock::LBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

LBlock::~LBlock() {}
BlockType LBlock::getBlockType() {
	return BlockType::L;
}





/*****************************************************************************/

OBlock::OBlock(bool isHeavy): Block(isHeavy) {
    type = 'O';
    Info i;
    i.col = 0;
    i.state = StateType::NONE;
    i.block = BlockType::O;
    for(int c = 0;c < 2;c++) {
      i.col = c;
      i.row = 0;
      cells.emplace_back(Cell(i));
      i.row = 1;
      cells.emplace_back(Cell(i));
    }
}
// OBlock::OBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// OBlock::OBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

OBlock::~OBlock() {}
BlockType OBlock::getBlockType() {
	return BlockType::O;
}




/*****************************************************************************/
SBlock::SBlock(bool isHeavy): Block(isHeavy) {
    type = 'S'; 
    Info i;
    i.row = 1;
    i.col = 0;
    i.state = StateType::NONE;
    i.block = BlockType::S;
    for(int c = 0;c < 3;c++) {
      i.col = c;
      cells.emplace_back(Cell(i));
      if(c == 1){
         i.row = 0;
         cells.emplace_back(Cell(i));
      }
    }
}
// SBlock::SBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// SBlock::SBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

SBlock::~SBlock() {}

BlockType SBlock::getBlockType() {
	return BlockType::S;
}



/*****************************************************************************/

TBlock::TBlock(bool isHeavy): Block(isHeavy) {
    type = 'T'; 
    Info i;
    i.row = 1;
    i.col = 1;
    i.state = StateType::NONE;
    i.block = BlockType::T;
    cells.emplace_back(Cell(i));
    i.row = 0;
    for(int c = 0;c < 3;c++) {
      i.col = c;
      cells.emplace_back(Cell(i));
    }

}
// TBlock::TBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// TBlock::TBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

TBlock::~TBlock() {}

BlockType TBlock::getBlockType() {
	return BlockType::T;
}



/*****************************************************************************/
ZBlock::ZBlock(bool isHeavy): Block(isHeavy) {
    type = 'Z'; 
    Info i;
    i.row = 0;
    i.col = 0;
    i.state = StateType::NONE;
    i.block = BlockType::Z;
    for(int c = 0;c < 3;c++) {
      i.col = c;
      cells.emplace_back(Cell(i));
      if(c == 1){
         i.row = 1;
         cells.emplace_back(Cell(i));
      }
    }

}
// ZBlock::ZBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// ZBlock::ZBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

ZBlock::~ZBlock() {}

BlockType ZBlock::getBlockType() {
	return BlockType::Z;
}

