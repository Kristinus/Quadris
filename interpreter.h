#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "invalidinputexception.h"
#include "grid.h"

template <typename InfoType> class Observer;
class Info;
class Command;
struct ProcessedInput;

class Interpreter {
    std::map<std::string, std::shared_ptr<Command>> commandMap;
    std::map<std::string, std::string> keyMap;
    std::unique_ptr<Grid> grid;
    bool gameOver = false;
    void initCommandMap();
    void initKeyMap();
    ProcessedInput parseCommand(std::istream &, std::string);

public:
    Interpreter();
    Interpreter(int, std::shared_ptr<Observer<Info>> ob, std::string, int);
    void run();
    std::istream &run(std::istream &);
    bool run(std::string);
    bool reset(std::string);

    void operator()();
};

#endif
