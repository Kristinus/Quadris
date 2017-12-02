#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__
#include <string>
#include <iostream>
#include <map>
// #include "level.h"
// #include "block.h"
// #include "grid.h"
// #include "graphicsDisplay.h"
class Grid;
class GraphicsDisplay;
class Command;
struct ProcessedInput;

class Interpreter {
	std::istream *in = &std::cin;
    std::map<std::string, Command *> commandMap;

    GraphicsDisplay *gd = nullptr;
    Grid *grid = nullptr;
    // Level level;

    void initCommandMap();
    ProcessedInput parseCommand(std::string);
public:
    Interpreter(int, bool, std::string, int);
    ~Interpreter();
    void run();

};

#endif
