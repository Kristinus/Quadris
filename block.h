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

	bool isValidCoordinate(int row , int col);
public:
    Block(BlockType, int level, bool isHeavy=false);
    Block(const Block&);
    // Block(int col, int row, bool isHeavy, int level, std::vector<Cell> cells, Grid* theGrid);
    // Block(bool isHeavy, int level, std::vector<Cell> cells);
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
	void setBlockCellTypes(BlockType);



    int getBottomLeftCol();
    int getBottomLeftRow();
    void playBlock();
    void setBottomLeftCoords(int row, int col);
    void moveTo(int row, int col);
    void left(int x=1);
    void right(int x=1);
    void down(int x=1);
    void clockwise(int x=1);
    void counterclockwise(int x =1);
    void updateSetCells(unsigned int);
    virtual Block* clone() const;

    virtual BlockType getBlockType();

friend std::ostream &operator<<(std::ostream &out, Block *);
};

#endif
