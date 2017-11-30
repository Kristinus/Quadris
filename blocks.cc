#include "blocks.h"

IBlock::IBlock(bool isHeavy): Block(isHeavy) {
    type = 'I';
}
// IBlock::IBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// IBlock::IBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

IBlock::~IBlock() {}



/*****************************************************************************/

JBlock::JBlock(bool isHeavy): Block(isHeavy) {
    type = 'J';
}
// JBlock::JBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// JBlock::JBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

JBlock::~JBlock() {}



/*****************************************************************************/

LBlock::LBlock(bool isHeavy): Block(isHeavy) {
    type = 'L';
}
// LBlock::LBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// LBlock::LBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

LBlock::~LBlock() {}



/*****************************************************************************/

OBlock::OBlock(bool isHeavy): Block(isHeavy) {
    type = 'O';
}
// OBlock::OBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// OBlock::OBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

OBlock::~OBlock() {}




/*****************************************************************************/
SBlock::SBlock(bool isHeavy): Block(isHeavy) {
    type = 'S';
}
// SBlock::SBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// SBlock::SBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

SBlock::~SBlock() {}



/*****************************************************************************/

TBlock::TBlock(bool isHeavy): Block(isHeavy) {
    type = 'T';
}
// TBlock::TBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// TBlock::TBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

TBlock::~TBlock() {}



/*****************************************************************************/
ZBlock::ZBlock(bool isHeavy): Block(isHeavy) {
    type = 'Z';
}
// ZBlock::ZBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// ZBlock::ZBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

ZBlock::~ZBlock() {}

