#ifndef LEVEL_H
#define LEVEL_H
#include "block.h"
#include "blocks.h"


class Level {
    int seed;
public:
    void setSeed(int);
    virtual int getLevel() = 0;
    virtual Block *createBlock();
    virtual ~Level();
    virtual Level *levelUp() = 0;
    virtual Level *levelDown() = 0;

};

#endif
