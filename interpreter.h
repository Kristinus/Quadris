#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__
#include <string>
#include <iostream>
#include <map>
#include <memory>
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
    std::map<std::string, std::shared_ptr<Command>> commandMap;

    GraphicsDisplay *gd = nullptr;
    Grid *grid = nullptr;
    // Level level;
    bool gameOver = false;

    void initCommandMap();
    ProcessedInput parseCommand(std::istream &, std::string);
public:
    Interpreter(int, bool, std::string, int);
    ~Interpreter();
    void run();
    void run(std::istream &);

};

#endif
