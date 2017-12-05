#ifndef LEVELS_H
#define LEVELS_H

#include "level.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

class Level0: public Level {
public:
    Level0(Grid *, int, std::string);
    std::unique_ptr<Block>createBlock() override;
    ~Level0() override; 
    Level *levelUp() override;
    Level *levelDown() override;
    int getLevel() override;
    void setRandom(bool) override;
    void restart() override;
};


class Level1: public Level {
public:
    Level1(Grid *, int, std::string);
    std::unique_ptr<Block>createBlock() override;
    Level *levelUp() override;
    Level *levelDown() override;
    int getLevel() override;
};


class Level2: public Level {
public:
    Level2(Grid *, int, std::string);
    std::unique_ptr<Block>createBlock() override;
    Level *levelUp() override;
    Level *levelDown() override;
    int getLevel() override;
};


class Level3: public Level {
public:
    Level3(Grid *, int, std::string);
    std::unique_ptr<Block>createBlock() override;
    Level *levelUp() override;
    Level *levelDown() override;
    int getLevel() override;
};


class Level4: public Level {
    int counter;
public:
    Level4(Grid *, int, std::string);
    std::unique_ptr<Block>createBlock() override;
    Level *levelUp() override;
    Level *levelDown() override;
    int getLevel() override;
    void restart() override;
    void setCounter(int) override;
};

#endif
