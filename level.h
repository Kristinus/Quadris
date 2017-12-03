#ifndef LEVEL_H
#define LEVEL_H
#include "block.h"
#include "blocks.h"
#include "info.h"
#include <functional>
#include <fstream>
#include <string>

class Grid;

class Level {
protected:
    Grid *grid = nullptr;
    int seed;
    std::ifstream seq;
    std::string sourceFile;
    std::string randFile;
    std::vector<std::function<Block *(int, bool)>> selector;
    bool heavy = false;
    bool random = true;
    Block *generateFromFile(bool);
public:
    Level(Grid *,int, std::string, bool);
    void setDefaultSelector(int, int, int, int, int, int, int);
    void setSeed(int);
    void setRandom(bool);
    void setFile(std::string);
    bool isHeavy();
    Block *getBlock(char);
    Block *getBlock(BlockType);
    virtual int getLevel() = 0;
    virtual Block *createBlock() = 0;
    virtual ~Level();
    virtual Level *levelUp() = 0;
    virtual Level *levelDown() = 0;
    virtual void restart();

};

#endif
