#ifndef LEVEL_H
#define LEVEL_H
#include "block.h"
#include "blocks.h"
#include <functional>

class Level {
protected:
    int seed;
    std::vector<std::function<Block *(int, bool)>> selector;
public:
    Level();
    Level(int seed);
    void setDefaultSelector(int, int, int, int, int, int, int);
    void setSeed(int);
    virtual int getLevel() = 0;
    virtual Block *createBlock() = 0;
    virtual ~Level();
    virtual Level *levelUp() = 0;
    virtual Level *levelDown() = 0;

};

#endif
