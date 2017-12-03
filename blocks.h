#ifndef __BLOCKS_H__
#define __BLOCKS_H__
#include "block.h"
#include "info.h"

class IBlock: public Block {
	
public:
    IBlock(int level, bool isHeavy = false);
    IBlock* clone() const;
	// IBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // IBlock(int level, bool isHeavy, int level, std::vector<Cell> cells);
    ~IBlock();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class JBlock: public Block {
	
public:
    JBlock(int level, bool isHeavy = false);
    JBlock* clone() const;

	// JBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // JBlock(int level, bool isHeavy, int level, std::vector<Cell> cells);
    ~JBlock();

    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class LBlock: public Block {
	
public:
    LBlock(int level, bool isHeavy = false);
    LBlock* clone() const;

	// LBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // LBlock(int level, bool isHeavy, int level, std::vector<Cell> cells);
    ~LBlock();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class OBlock: public Block {
	
public:
    OBlock(int level, bool isHeavy = false);
    OBlock* clone() const;

	// OBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // OBlock(int level, bool isHeavy, int level, std::vector<Cell> cells);
    ~OBlock();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class SBlock: public Block {
	
public:
	SBlock(int level, bool isHeavy = false);
	SBlock* clone() const;

    // SBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // SBlock(int level, bool isHeavy, int level, std::vector<Cell> cells);
    ~SBlock();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class TBlock: public Block {
	
public:
    TBlock(int level, bool isHeavy = false);
    TBlock* clone() const;

	// TBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // TBlock(int level, bool isHeavy, int level, std::vector<Cell> cells);
    ~TBlock();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};

class ZBlock: public Block {
	
public:
    ZBlock(int level, bool isHeavy = false);
    ZBlock* clone() const;

	// ZBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // ZBlock(int level, bool isHeavy, int level, std::vector<Cell> cells);
    ~ZBlock();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};


class DotBlock: public Block {

public:
    DotBlock(int level, bool isHeavy = false);
    DotBlock* clone() const;

	// DotBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells);
    // DotBlock(int level, bool isHeavy, int level, std::vector<Cell> cells);
    ~DotBlock();
    // void clockwise(int x=1) override;
    // void counterclockwise(int x=1) override;
};



#endif
