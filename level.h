#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"
#include "blocks.h"
#include "info.h"
#include <functional>
#include <fstream>
#include <string>
#include <memory>

class Grid;

class Level {
protected:
    Grid *grid = nullptr;
    int seed;
    std::ifstream seq;
    std::string sourceFile;
    std::string randFile;
    std::vector<std::function<std::unique_ptr<Block>(int, bool)>> selector;
    bool heavy = false;
    bool random = true;
    std::unique_ptr<Block> generateFromFile(bool);

public:
    Level(Grid *,int, std::string, bool);
    virtual ~Level();
    void setSelector(int, int, int, int, int, int, int);
    void setSeed(int);
    void setRandom(bool);
    void setFile(std::string);
    bool isHeavy();
    std::unique_ptr<Block> getBlock(char, int, bool);
    std::unique_ptr<Block> getBlock(BlockType, int, bool);
    virtual int getLevel() = 0;
    virtual std::unique_ptr<Block> createBlock() = 0;
    virtual Level *levelUp() = 0;
    virtual Level *levelDown() = 0;
    virtual void restart();
    virtual void setCounter(int);
};

#endif
