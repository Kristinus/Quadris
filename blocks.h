#ifndef __BLOCKS_H__
#define __BLOCKS_H__
#include "block.h"

class LBlock: public Block {
	
public:
	LBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
   LBlock(bool isHeavy, int level, std::vector<Cell> cells);
   ~LBlock() = 0;
   void clockwise() override;
   void counterclockwise() override;
};

#endif
