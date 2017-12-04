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


ZBlock::~ZBlock() {}

/*****************************************************************************/

DotBlock::DotBlock(int level, bool isHeavy): Block(BlockType::DOT, level, isHeavy) {
    type = '*'; 
    Info i;

    // Initializes dot block cell
    i.row = 0;
    i.col = 0;
    i.state = StateType::STATIC;
    i.block = BlockType::DOT;
    cells.emplace_back(Cell(i));
}


DotBlock::~DotBlock() {}

