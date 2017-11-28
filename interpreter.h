#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__
#include <string>
#include <iostream>
// #include "level.h"
// #include "block.h"
// #include "grid.h"
#include "graphicsDisplay.h"

class Interpreter {
	std::istream *in = &std::cin;
   // GraphicsDisplay *gd;
    // Grid grid;
    // Level level;


	public:
    Interpreter(std::string, bool, std::string, int);
    ~Interpreter();
    void run();

};

#endif
