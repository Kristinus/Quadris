#ifndef __BLOCKS_H__
#define __BLOCKS_H__
#include "block.h"
#include "info.h"

class IBlock: public Block {
	
public:
    IBlock(int level, bool isHeavy = false);
	// IBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // IBlock(int level, bool isHeavy, int level, std::vector<Cell> cells);
    ~IBlock();
    BlockType getBlockType();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class JBlock: public Block {
	
public:
    JBlock(int level, bool isHeavy = false);
	// JBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // JBlock(int level, bool isHeavy, int level, std::vector<Cell> cells);
    ~JBlock();
    BlockType getBlockType();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class LBlock: public Block {
	
public:
    LBlock(int level, bool isHeavy = false);
	// LBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // LBlock(int level, bool isHeavy, int level, std::vector<Cell> cells);
    ~LBlock();
    BlockType getBlockType();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class OBlock: public Block {
	
public:
    OBlock(int level, bool isHeavy = false);
	// OBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // OBlock(int level, bool isHeavy, int level, std::vector<Cell> cells);
    ~OBlock();
    BlockType getBlockType();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class SBlock: public Block {
	
public:
	SBlock(int level, bool isHeavy = false);
    // SBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // SBlock(int level, bool isHeavy, int level, std::vector<Cell> cells);
    ~SBlock();
    BlockType getBlockType();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class TBlock: public Block {
	
public:
    TBlock(int level, bool isHeavy = false);
	// TBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // TBlock(int level, bool isHeavy, int level, std::vector<Cell> cells);
    ~TBlock();
    BlockType getBlockType();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class ZBlock: public Block {
	
public:
    ZBlock(int level, bool isHeavy = false);
	// ZBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // ZBlock(int level, bool isHeavy, int level, std::vector<Cell> cells);
    ~ZBlock();
    BlockType getBlockType();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

#endif
