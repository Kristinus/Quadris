#ifndef LEVEL_H
#define LEVEL_H
#include "block.h"
#include "blocks.h"


class Level {
    int seed;
protected:
    std::vector<Block *> selector;
public:
    void setDefaultSelector();
    void setSeed(int);
    virtual int getLevel() = 0;
    virtual Block *createBlock() = 0;
    virtual ~Level();
    virtual Level *levelUp() = 0;
    virtual Level *levelDown() = 0;

};

#endif
