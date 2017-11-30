#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "info.h"
#include "cell.h"
#include <vector>
class Grid;

class Block {
protected:
    std::vector<Cell> cells;
    bool isHeavy;
    int level;
    int col;
    int row;
    Grid *grid;
    void rotate();
public:
    Block(bool isHeavy=false);
    Block(int col, int row, bool isHeavy, int level, std::vector<Cell> cells, Grid* theGrid);
    // Block(bool isHeavy, int level, std::vector<Cell> cells);
    ~Block();
    void move();
    std::vector<Cell> getBlockCells();
    bool isBlockHeavy();
    int getLevel();
    void move(int, int);
    void left();
    void right();
    void down();
    virtual void clockwise();
    virtual void counterclockwise();
    void updateSetCells(int);
};

#endif
