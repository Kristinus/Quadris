#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "info.h"
#include "cell.h"

class Block {
    std::vector<Cell> cells;
public:
    Block(int n);
};

#endif
