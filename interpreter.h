#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__
#include <string>
#include <iostream>
// #include "level.h"
// #include "block.h"
// #include "grid.h"
// #include "graphicsDisplay.h"
class Grid;

class Interpreter {
	std::istream *in = &std::cin;
    std::map<std::string, Command *> commandMap;
   // GraphicsDisplay *gd;
    Grid *grid = nullptr;
    // Level level;

    void initCommandMap();
public:
    Interpreter(std::string, bool, std::string, int);
    ~Interpreter();
    void run();

};

#endif
