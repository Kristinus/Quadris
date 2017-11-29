#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "info.h"
#include "cell.h"
#include <vector>

class Block {
    std::vector<Cell> cells;
    bool isHeavy;
    int level;
    int col;
    int row;
public:
    Block(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    Block(bool isHeavy, int level, std::vector<Cell> cells);
    ~Block();
    std::vector<Cell> getBlockCells();
    bool isBlockHeavy();
    int getLevel();
    void left();
    void right();
    void down();
    virtual void clockwise()=0;
    virtual void counterclockwise()=0;
};

#endif
