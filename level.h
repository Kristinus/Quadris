#ifndef LEVEL_H
#define LEVEL_H
#include "block.h"
#include "blocks.h"


class Level {
    int seed;
public:
    void setSeed(int);
    virtual Block *createBlock();
    virtual ~Level();
};

#endif
