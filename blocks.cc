#include "blocks.h"
#include "info.h"
#include <memory>

IBlock::IBlock(int level, bool isHeavy): Block(BlockType::I, level, isHeavy) {
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

// IBlock* IBlock::clone() const {
// 	return new IBlock(level, isHeavy);
	
// }
// IBlock::IBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// IBlock::IBlock(int level, bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

IBlock::~IBlock() {}


/*****************************************************************************/

JBlock::JBlock(int level, bool isHeavy): Block(BlockType::J, level, isHeavy) {
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

// JBlock* JBlock::clone() const {
// 	JBlock *cpy = new JBlock(level, isHeavy);
// 	return cpy;
// }
// JBlock::JBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// JBlock::JBlock(int level, bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

JBlock::~JBlock() {}

/*****************************************************************************/

LBlock::LBlock(int level, bool isHeavy): Block(BlockType::L, level, isHeavy) {
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

// LBlock* LBlock::clone() const {
// 	LBlock *cpy = new LBlock(level, isHeavy);
// 	return cpy;
// }
// LBlock::LBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// LBlock::LBlock(int level, bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

LBlock::~LBlock() {}





/*****************************************************************************/

OBlock::OBlock(int level, bool isHeavy): Block(BlockType::O, level, isHeavy) {
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

// OBlock* OBlock::clone() const {
// 	OBlock *cpy = new OBlock(level, isHeavy);
// 	return cpy;
// }


/*****************************************************************************/
SBlock::SBlock(int level, bool isHeavy): Block(BlockType::S, level, isHeavy) {
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

// SBlock* SBlock::clone() const {
// 	SBlock *cpy = new SBlock(level, isHeavy);
// 	return cpy;
// }



/*****************************************************************************/

TBlock::TBlock(int level, bool isHeavy): Block(BlockType::T, level, isHeavy) {
    type = 'T'; 

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

// TBlock* TBlock::clone() const {
// 	TBlock *cpy = new TBlock(level, isHeavy);
// 	return cpy;
// }

// TBlock::TBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// TBlock::TBlock(int level, bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

TBlock::~TBlock() {}



/*****************************************************************************/
ZBlock::ZBlock(int level, bool isHeavy): Block(BlockType::Z, level, isHeavy) {
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
// ZBlock* ZBlock::clone() const {
// 	ZBlock *cpy = new ZBlock(level, isHeavy);
// 	return cpy;
// }
// ZBlock::ZBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// ZBlock::ZBlock(int level, bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

ZBlock::~ZBlock() {}

/*****************************************************************************/

DotBlock::DotBlock(int level, bool isHeavy): Block(BlockType::DOT, level, isHeavy) {
    type = '*'; 
    Info i;
    i.row = 0;
    i.col = 0;
    i.state = StateType::STATIC;
    i.block = BlockType::DOT;
    cells.emplace_back(Cell(i));
}
// DotBlock* DotBlock::clone() const {
// 	DotBlock *cpy = new DotBlock(level, isHeavy);
// 	return cpy;
// }
// DotBlock::DotBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

// DotBlock::DotBlock(int level, bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

DotBlock::~DotBlock() {}

