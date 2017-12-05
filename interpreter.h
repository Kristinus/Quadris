#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "invalidinputexception.h"
#include "grid.h"
#include "interpreterimpl.h"

template <typename InfoType> class Observer;
class Info;
class Command;
struct ProcessedInput;
class InterpreterImpl;

class Interpreter {
    std::map<std::string, std::shared_ptr<Command>> commandMap;
    std::map<std::string, std::string> keyMap;
    std::unique_ptr<Grid> grid;
    bool gameOver = false;
    std::unique_ptr<InterpreterImpl> pImpl;
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
