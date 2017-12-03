#ifndef LEVELS_H
#define LEVELS_H
#include "level.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

class Level0: public Level {
public:
    Level0(int seed, std::string);
    Block *createBlock() override;
    ~Level0() override; 
    Level *levelUp();
    Level *levelDown();
    int getLevel();
};

class Level1: public Level {
public:
    Level1(int seed, std::string);
    Block *createBlock() override;
    Level *levelUp();
    Level *levelDown();
    int getLevel();

};

class Level2: public Level {
public:
    Level2(int seed, std::string);
    Block *createBlock() override;
    Level *levelUp();
    Level *levelDown();
    int getLevel();

};

class Level3: public Level {
public:
    Level3(int seed, std::string);
    Block *createBlock() override;
    Level *levelUp();
    Level *levelDown();
    int getLevel();

};

class Level4: public Level {
    int counter;
public:
    Level4(int seed, std::string);
    Block *createBlock() override;
    Level *levelUp();
    Level *levelDown();
    int getLevel();

};
#endif
