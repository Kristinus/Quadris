#ifndef LEVELS_H
#define LEVELS_H
#include "level.h"
#include <iostream>
#include <fstream>

class Level0: public Level {
    std::ifstream seq;
    std::string sourceFile = "sequence.txt";
public:
    Level0();
    Block createBlock() override;
};

class Level1: public Level {
public:
    Level1();
    Block createBlock() override;
};

class Level2: public Level {
public:
    Level2();
    Block createBlock() override;
};

class Level3: public Level {
public:
    Level3();
    Block createBlock() override;
};

class Level4: public Level {
public:
    Level4();
    Block createBlock() override;
};
#endif
