#ifndef LEVELS_H
#define LEVELS_H
#include "level.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

class Level0: public Level {
    std::ifstream seq;
    std::string sourceFile = "sequence.txt";
public:
    Level0();
    Level0(int seed);
    Block *createBlock() override;
    ~Level0() override; 
    Level *levelUp();
    Level *levelDown();
    int getLevel();
};

class Level1: public Level {
public:
    Level1();
    Level1(int seed);
    Block *createBlock() override;
    Level *levelUp();
    Level *levelDown();
    int getLevel();

};

class Level2: public Level {
public:
    Level2();
    Level2(int seed);
    Block *createBlock() override;
    Level *levelUp();
    Level *levelDown();
    int getLevel();

};

class Level3: public Level {
public:
    Level3();
    Level3(int seed);
    Block *createBlock() override;
    Level *levelUp();
    Level *levelDown();
    int getLevel();

};

class Level4: public Level {
public:
    Level4();
    Level4(int seed);
    Block *createBlock() override;
    Level *levelUp();
    Level *levelDown();
    int getLevel();

};
#endif
