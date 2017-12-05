#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "info.h"
#include "cell.h"
#include <vector>
#include <iostream>
#include <memory>

class Grid;
template <typename InfoType> class Observer;

class Block {
protected:
    std::vector<Cell> cells;
    bool isHeavy;
    int level;
    int col;
    int row;
    Grid *grid = nullptr;
    char type;
    BlockType blockType;
    bool isValidRotation(Block *b, std::vector<int> rotatedRow, 
    	std::vector<int> rotatedCol);
	 bool isValidCoordinate(int row , int col) const;
	 void move(int, int);

public:
    Block(BlockType, int level, bool isHeavy=false);
    virtual std::unique_ptr<Block> clone() const = 0;
    virtual ~Block() = 0;
    void setGridPointer(Grid *);
    void move();
    void rotate(int);
    std::vector<Cell> getBlockCells();
    bool isBlockHeavy() const;
    int getLevel() const;
    int getBottomLeftCol() const;
    int getBottomLeftRow() const;
    void moveTo(int row, int col);
    void left(int x=1);
    void right(int x=1);
    void down(int x=1);
    void clockwise(int x=1);
    void counterclockwise(int x =1);
    void updateSetCells(std::vector<size_t>);
    virtual BlockType getBlockType() const;

    friend std::ostream &operator<<(std::ostream &out, Block *);
};

#endif
