#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "invalidinputexception.h"

class Grid;
template <typename InfoType> class Observer;
class Info;
class Command;
struct ProcessedInput;

class Interpreter {
	std::istream *in = &std::cin;
    std::map<std::string, std::shared_ptr<Command>> commandMap;
    // GraphicsDisplay *gd = nullptr;
    Grid *grid = nullptr;
    bool gameOver = false;
    void initCommandMap();
    ProcessedInput parseCommand(std::istream &, std::string);
public:
    Interpreter(int, Observer<Info> *ob, std::string, int);
    ~Interpreter();
    void run();
    void run(std::istream &);

    void operator()();
};

#endif
