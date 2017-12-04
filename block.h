#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "info.h"
#include "cell.h"
#include <vector>
#include <iostream>
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
    bool isValidRotation(Block *b, std::vector<int> rotatedRow, std::vector<int> rotatedCol);
	 bool isValidCoordinate(int row , int col);
public:
    Block(BlockType, int level, bool isHeavy=false);
    Block(const Block&);
    virtual ~Block();
    void setGridPointer(Grid *);
    void displayNext(Observer<Info> *ob);
    void move();
    void rotate(int);
    std::vector<Cell> getBlockCells();
    bool isBlockHeavy();
    int getLevel();
    void move(int, int);
	void setBlockCellStates(StateType s);
    int getBottomLeftCol();
    int getBottomLeftRow();
    void moveTo(int row, int col);
    void left(int x=1);
    void right(int x=1);
    void down(int x=1);
    void clockwise(int x=1);
    void counterclockwise(int x =1);
    void updateSetCells(std::vector<size_t>);
    virtual BlockType getBlockType();

    friend std::ostream &operator<<(std::ostream &out, Block *);
};

#endif
