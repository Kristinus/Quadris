#ifndef __BLOCKS_H__
#define __BLOCKS_H__
#include "block.h"
#include "info.h"

class IBlock: public Block {
public:
    IBlock(int level, bool isHeavy = false);
    IBlock* clone() const override;
    ~IBlock();
};


class JBlock: public Block {
public:
    JBlock(int level, bool isHeavy = false);
    JBlock* clone() const override;
    ~JBlock();
};


class LBlock: public Block {
public:
    LBlock(int level, bool isHeavy = false);
    LBlock* clone() const override;
    ~LBlock();
};


class OBlock: public Block {
public:
    OBlock(int level, bool isHeavy = false);
    OBlock* clone() const override;
    ~OBlock();
};


class SBlock: public Block {
public:
	SBlock(int level, bool isHeavy = false);
	SBlock* clone() const override;
   ~SBlock();
};


class TBlock: public Block {
public:
    TBlock(int level, bool isHeavy = false);
    TBlock* clone() const override;
    ~TBlock();
};


class ZBlock: public Block {	
public:
    ZBlock(int level, bool isHeavy = false);
    ZBlock* clone() const override;
    ~ZBlock();
};


class DotBlock: public Block {
public:
    DotBlock(int level, bool isHeavy = false);
    DotBlock* clone() const override;
    ~DotBlock();
};

#endif
