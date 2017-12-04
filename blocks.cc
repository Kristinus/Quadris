#include "blocks.h"
#include "info.h"
#include <memory>

IBlock::IBlock(int level, bool isHeavy): Block(BlockType::I, level, isHeavy) {
    type = 'I';
    Info i;
    
    // Initializes I block cells
    i.row = 0;
    i.state = StateType::NEXT;
    i.block = BlockType::I;
    for(int c=0; c<4; c++) {
        i.col = c;
        cells.emplace_back(Cell(i));   
    }
}

std::unique_ptr<Block> IBlock::clone() const {
	std::unique_ptr<IBlock> cpy (new IBlock(level, isHeavy));
	cpy->type = type;
	cpy->blockType = blockType;
	cpy->grid = grid;
	cpy->row = row;
	cpy->col = col;
	cpy->cells = cells;
	return cpy;
}


IBlock::~IBlock() {}

/*****************************************************************************/

JBlock::JBlock(int level, bool isHeavy): Block(BlockType::J, level, isHeavy) {
    type = 'J';
    Info i;

    // Initializes J block cells
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
}

std::unique_ptr<Block> JBlock::clone() const {
	std::unique_ptr<JBlock> cpy (new JBlock(level, isHeavy));
	cpy->type = type;
	cpy->blockType = blockType;
	cpy->grid = grid;
	cpy->row = row;
	cpy->col = col;
	cpy->cells = cells;

	return cpy;
}


JBlock::~JBlock() {}

/*****************************************************************************/

LBlock::LBlock(int level, bool isHeavy): Block(BlockType::L, level, isHeavy) {
    type = 'L';
    Info i;
    
    // Initializes L block cells
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

std::unique_ptr<Block> LBlock::clone() const {
	std::unique_ptr<LBlock> cpy (new LBlock(level, isHeavy));
	cpy->type = type;
	cpy->blockType = blockType;
	cpy->grid = grid;
	cpy->row = row;
	cpy->col = col;
	cpy->cells = cells;
	return cpy;
}

LBlock::~LBlock() {}

/*****************************************************************************/

OBlock::OBlock(int level, bool isHeavy): Block(BlockType::O, level, isHeavy) {
    type = 'O';
    Info i;

    // Initializes O block cells
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


std::unique_ptr<Block> OBlock::clone() const {
	std::unique_ptr<OBlock> cpy (new OBlock(level, isHeavy));
	cpy->type = type;
	cpy->blockType = blockType;
	cpy->grid = grid;
	cpy->row = row;
	cpy->col = col;
	cpy->cells = cells;

	return cpy;
}

OBlock::~OBlock() {}

/*****************************************************************************/

SBlock::SBlock(int level, bool isHeavy): Block(BlockType::S, level, isHeavy) {
    type = 'S'; 
    Info i;

    // Initializes S block cells
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

std::unique_ptr<Block> SBlock::clone() const {
	std::unique_ptr<SBlock> cpy (new SBlock(level, isHeavy));
	cpy->type = type;
	cpy->blockType = blockType;
	cpy->grid = grid;
	cpy->row = row;
	cpy->col = col;
	cpy->cells = cells;

	return cpy;
}



SBlock::~SBlock() {}

/*****************************************************************************/

TBlock::TBlock(int level, bool isHeavy): Block(BlockType::T, level, isHeavy) {
    type = 'T'; 
    Info i;

    // Initializes T block cells
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


std::unique_ptr<Block> TBlock::clone() const {
	std::unique_ptr<TBlock> cpy (new TBlock(level, isHeavy));
	cpy->type = type;
	cpy->blockType = blockType;
	cpy->grid = grid;
	cpy->row = row;
	cpy->col = col;
	cpy->cells = cells;

	return cpy;
}

TBlock::~TBlock() {}

/*****************************************************************************/
ZBlock::ZBlock(int level, bool isHeavy): Block(BlockType::Z, level, isHeavy) {
    type = 'Z'; 
    Info i;

    // Initializes Z block cells
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

std::unique_ptr<Block> ZBlock::clone() const {
	std::unique_ptr<ZBlock> cpy (new ZBlock(level, isHeavy));
	cpy->type = type;
	cpy->blockType = blockType;
	cpy->grid = grid;
	cpy->row = row;
	cpy->col = col;
	cpy->cells = cells;

	return cpy;
}

ZBlock::~ZBlock() {}

/*****************************************************************************/

DotBlock::DotBlock(int level, bool isHeavy): 
Block(BlockType::DOT, level, isHeavy) {
    type = '*'; 
    Info i;

    // Initializes dot block cell
    i.row = 0;
    i.col = 0;
    i.state = StateType::STATIC;
    i.block = BlockType::DOT;
    cells.emplace_back(Cell(i));
}

std::unique_ptr<Block> DotBlock::clone() const {
	std::unique_ptr<DotBlock> cpy(new DotBlock(level, isHeavy));
	cpy->type = type;
	cpy->blockType = blockType;
	cpy->grid = grid;
	cpy->row = row;
	cpy->col = col;
	cpy->cells = cells;

	return cpy;
}

DotBlock::~DotBlock() {}

