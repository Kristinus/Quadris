#ifndef __BLOCKS_H__
#define __BLOCKS_H__
#include "block.h"
#include "info.h"

class IBlock: public Block {
	
public:
    IBlock(bool isHeavy = false);
	// IBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // IBlock(bool isHeavy, int level, std::vector<Cell> cells);
    ~IBlock();
    BlockType getBlockType();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class JBlock: public Block {
	
public:
    JBlock(bool isHeavy = false);
	// JBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // JBlock(bool isHeavy, int level, std::vector<Cell> cells);
    ~JBlock();
    BlockType getBlockType();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class LBlock: public Block {
	
public:
    LBlock(bool isHeavy = false);
	// LBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // LBlock(bool isHeavy, int level, std::vector<Cell> cells);
    ~LBlock();
    BlockType getBlockType();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class OBlock: public Block {
	
public:
    OBlock(bool isHeavy = false);
	// OBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // OBlock(bool isHeavy, int level, std::vector<Cell> cells);
    ~OBlock();
    BlockType getBlockType();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class SBlock: public Block {
	
public:
	SBlock(bool isHeavy = false);
    // SBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // SBlock(bool isHeavy, int level, std::vector<Cell> cells);
    ~SBlock();
    BlockType getBlockType();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class TBlock: public Block {
	
public:
    TBlock(bool isHeavy = false);
	// TBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // TBlock(bool isHeavy, int level, std::vector<Cell> cells);
    ~TBlock();
    BlockType getBlockType();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class ZBlock: public Block {
	
public:
    ZBlock(bool isHeavy = false);
	// ZBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // ZBlock(bool isHeavy, int level, std::vector<Cell> cells);
    ~ZBlock();
    BlockType getBlockType();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

#endif
