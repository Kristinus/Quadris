#include "blocks.h"

IBlock::IBlock(bool isHeavy): Block(isHeavy) {}
// IBlock::IBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// IBlock::IBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

IBlock::~IBlock() {}

void IBlock::clockwise() {
   
}

void IBlock::counterclockwise() {

}

/*****************************************************************************/

JBlock::JBlock(bool isHeavy): Block(isHeavy) {}
// JBlock::JBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// JBlock::JBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

JBlock::~JBlock() {}

void JBlock::clockwise() {
   
}

void JBlock::counterclockwise() {

}

/*****************************************************************************/

LBlock::LBlock(bool isHeavy): Block(isHeavy) {}
// LBlock::LBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// LBlock::LBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

LBlock::~LBlock() {}

void LBlock::clockwise() {
   
}

void LBlock::counterclockwise() {

}

/*****************************************************************************/

OBlock::OBlock(bool isHeavy): Block(isHeavy) {}
// OBlock::OBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// OBlock::OBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

OBlock::~OBlock() {}

void OBlock::clockwise() {
   
}

void OBlock::counterclockwise() {

}

/*****************************************************************************/
SBlock::SBlock(bool isHeavy): Block(isHeavy) {}
// SBlock::SBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// SBlock::SBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

SBlock::~SBlock() {}

void SBlock::clockwise() {
   
}

void SBlock::counterclockwise() {

}

/*****************************************************************************/

TBlock::TBlock(bool isHeavy): Block(isHeavy) {}
// TBlock::TBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// TBlock::TBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

TBlock::~TBlock() {}

void TBlock::clockwise() {
   
}

void TBlock::counterclockwise() {

}

/*****************************************************************************/
ZBlock::ZBlock(bool isHeavy): Block(isHeavy) {}
// ZBlock::ZBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// ZBlock::ZBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

ZBlock::~ZBlock() {}

void ZBlock::clockwise() {
   
}

void ZBlock::counterclockwise() {

}

/*****************************************************************************/

