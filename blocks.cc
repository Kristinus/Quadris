#include "blocks.h"
#include "info.h"

IBlock::IBlock(int level, bool isHeavy): Block(level, isHeavy) {
    type = 'I';
    Info i;
    i.row = 0;
    i.state = StateType::NEXT;
    i.block = BlockType::I;
    for(int c=0; c<4; c++) {
        i.col = c;
        cells.emplace_back(Cell(i));   
    }
}

IBlock* IBlock::clone() const {
	IBlock *cpy = new IBlock(level, isHeavy);
	return cpy;
}
// IBlock::IBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// IBlock::IBlock(int level, bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

IBlock::~IBlock() {}
BlockType IBlock::getBlockType() {
	return BlockType::I;
}



/*****************************************************************************/

JBlock::JBlock(int level, bool isHeavy): Block(level, isHeavy) {
    type = 'J';
    Info i;
    
    i.state = StateType::NEXT;
    i.block = BlockType::J;
    i.col = 0;
    i.row = 1;
    cells.emplace_back(Cell(i));
    i.row = 0;
    i.state = StateType::NEXT;
    i.block = BlockType::J;
    for(int c=0; c<3; c++) {
        i.col = c;
        cells.emplace_back(Cell(i));   
    }
    
    
 //       row = 0;
   // col  = 0;
}

JBlock* JBlock::clone() const {
	JBlock *cpy = new JBlock(level, isHeavy);
	return cpy;
}
// JBlock::JBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// JBlock::JBlock(int level, bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

JBlock::~JBlock() {}
BlockType JBlock::getBlockType() {
	return BlockType::J;
}



/*****************************************************************************/

LBlock::LBlock(int level, bool isHeavy): Block(level, isHeavy) {
    type = 'L';
    Info i;
    i.state = StateType::NEXT;
    i.block = BlockType::L;

    i.row = 1;
    i.col = 2;
    cells.emplace_back(Cell(i));
    i.row = 0;
    for(int c = 0;c < 3; c++) {
        i.col = c;
        cells.emplace_back(Cell(i));
    }
    
    

}

LBlock* LBlock::clone() const {
	LBlock *cpy = new LBlock(level, isHeavy);
	return cpy;
}
// LBlock::LBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// LBlock::LBlock(int level, bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

LBlock::~LBlock() {}
BlockType LBlock::getBlockType() {
	return BlockType::L;
}





/*****************************************************************************/

OBlock::OBlock(int level, bool isHeavy): Block(level, isHeavy) {
    type = 'O';
    Info i;
    i.state = StateType::NEXT;
    i.block = BlockType::O;
    for(int r = 1; r >=0 ; r--) {
        i.row = r;
        i.col = 0;
        cells.emplace_back(Cell(i));
        i.col = 1;
        cells.emplace_back(Cell(i));
    }
}
// OBlock::OBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// OBlock::OBlock(int level, bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

OBlock::~OBlock() {}
BlockType OBlock::getBlockType() {
	return BlockType::O;
}

OBlock* OBlock::clone() const {
	OBlock *cpy = new OBlock(level, isHeavy);
	return cpy;
}


/*****************************************************************************/
SBlock::SBlock(int level, bool isHeavy): Block(level, isHeavy) {
    type = 'S'; 
    Info i;
    i.row = 1;
    i.col = 1;
    i.state = StateType::NEXT;
    i.block = BlockType::S;
    cells.emplace_back(Cell(i));
    i.col = 2;
    cells.emplace_back(Cell(i));
    i.row = 0;
    i.col = 0;
    cells.emplace_back(Cell(i));
    i.col = 1;
    cells.emplace_back(Cell(i));
}
// SBlock::SBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// SBlock::SBlock(int level, bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

SBlock::~SBlock() {}

BlockType SBlock::getBlockType() {
	return BlockType::S;
}

SBlock* SBlock::clone() const {
	SBlock *cpy = new SBlock(level, isHeavy);
	return cpy;
}



/*****************************************************************************/

TBlock::TBlock(int level, bool isHeavy): Block(level, isHeavy) {
    type = 'T'; 
    grid = nullptr;

    Info i;
    i.state = StateType::NEXT;
    i.block = BlockType::T;
    i.row = 1;
    for(int c = 0;c < 3;c++) {
      i.col = c;
      cells.emplace_back(Cell(i));
    }
    i.col = 1;
    i.row = 0;
    cells.emplace_back(Cell(i));
}

TBlock* TBlock::clone() const {
	TBlock *cpy = new TBlock(level, isHeavy);
	return cpy;
}

// TBlock::TBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// TBlock::TBlock(int level, bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

TBlock::~TBlock() {}

BlockType TBlock::getBlockType() {
	return BlockType::T;
}



/*****************************************************************************/
ZBlock::ZBlock(int level, bool isHeavy): Block(level, isHeavy) {
    type = 'Z'; 
    Info i;
    i.row = 1;
    i.col = 0;
    i.state = StateType::NEXT;
    i.block = BlockType::Z;
    for(int c = 0;c < 3;c++) {
      i.col = c;
      cells.emplace_back(Cell(i));
      if(c == 1){
         i.row = 0;
         cells.emplace_back(Cell(i));
      }
    }


}
ZBlock* ZBlock::clone() const {
	ZBlock *cpy = new ZBlock(level, isHeavy);
	return cpy;
}
// ZBlock::ZBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// ZBlock::ZBlock(int level, bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

ZBlock::~ZBlock() {}

BlockType ZBlock::getBlockType() {
	return BlockType::Z;
}

