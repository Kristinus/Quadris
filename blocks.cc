#include "blocks.h"

IBlock::IBlock(bool isHeavy): Block(isHeavy) {
    type = 'I';
    Info i;
    i.row = 1;
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



/*****************************************************************************/

JBlock::JBlock(bool isHeavy): Block(isHeavy) {
    type = 'J';
    Info i;
    i.row = 0;
    i.col = 0;
    i.state = StateType::NONE;
    i.block = BlockType::I;
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

