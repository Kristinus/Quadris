#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "level.h"
#include "block.h"
#include "grid.h"
#include "commands.h"
#include "graphicsDisplay.h"
#include "interpreter.h"
using namespace std;

struct ProcessedInput {
	string command;

	int multiplier;



};

void Interpreter::initCommandMap() {
    commandMap["left"] = new LeftCommand(grid);
    commandMap["right"] = new RightCommand(grid);
    commandMap["down"] = new DownCommand(grid);
    commandMap["levelup"] = new LevelUpCommand(grid);
    commandMap["leveldown"] = new LevelDownCommand(grid);
    commandMap["norandom"] = new NoRandomCommand(grid);
    commandMap["sequence"] = new SequenceCommand(grid);
    commandMap["clockwise"] = new ClockwiseCommand(grid);
    commandMap["counterclockwise"] = new CounterClockwiseCommand(grid);
    commandMap["drop"] = new DropCommand(grid);
    commandMap["restart"] = new RestartCommand(grid);
    // commandMap["I"] = new ICommand(grid);
    // commandMap["J"] = new JCommand(grid);
    // commandMap["L"] = new LCommand(grid);
    // commandMap["O"] = new OCommand(grid);
    // commandMap["T"] = new TCommand(grid);
    // commandMap["Z"] = new ZCommand(grid);
    // commandMap["S"] = new SCommand(grid);
}

Interpreter::Interpreter(int seed, bool textOnly, string scriptFile, int startLevel) {
	if (textOnly == false) {
		gd = new GraphicsDisplay();
	}
	grid = new Grid(seed, gd, scriptFile);
    if(gd) gd->setGrid(grid);
    
    initCommandMap();
}

bool isDigit(char c) {
	if ((c >= '0') && (c <= '9')) return true;
	else return false;
}

// (TODO) put this into an exception class
// also learn how to make your own 

struct invalidInputException {
	string message;
	invalidInputException(string message):message{message} {}
};
 
ProcessedInput parseCommand(string command) {
	if (command == "") throw invalidInputException("Empty command");
	string bd = "";
	string typedCommand;
	int res;
	size_t i;
	for (i = 0; i < command.length(); i++) {
		if (isDigit(command[i])) {
			bd += command[i];
		} else {
			break;
		}
	}

	vector<string> possibleCommands {"left", "right", "down", "levelup", "leveldown", "norandom", "random", "sequence", "clockwise", "counterclockwise", "drop", "restart", "hint", "I", "J", "L", "O", "S", "Z", "T", "quit",};
    typedCommand = command.substr(i);
     
    for (int i = possibleCommands.size() - 1; i >= 0; i--) {

        string possibleCommand = possibleCommands[i];
        int partialCommandLen = typedCommand.length();
        if (typedCommand != possibleCommand.substr(0, partialCommandLen)) {
        	possibleCommands.erase(possibleCommands.begin() + i);
        }

    }

    if (possibleCommands.size() == 0) {
        	// throw an error

    	// (TODO) put these messages in a config file somewhere
    	throw invalidInputException("No Command Matches.");
    }

    else if (possibleCommands.size() > 1) {
    	throw invalidInputException("Ambiguous Input");
    	// throw an error: ambigious command
    }

    else {
    	typedCommand = possibleCommands[0];
    }

    if (bd != "") {
    	istringstream iss{bd};
		iss >> res; // throw an exception
		return ProcessedInput{possibleCommands[0], res};
    }
    else return ProcessedInput{possibleCommands[0], 1};
	

}

void Interpreter::run() {
    string s;
    // grid->initGrid();
    cout << *grid;
    while(*in >> s) {

    	ProcessedInput processedCommand;
        try {
        	 processedCommand = parseCommand(s);
        } catch (invalidInputException e) {
        	//cout << e.message << endl;
        	continue;
        }
        string cmd = processedCommand.command;
        int mult = processedCommand.multiplier;
        if (cmd == "quit") {
        	break;
        }

        // cout << cmd << "|" << mult << endl; 
        if (commandMap.count(cmd) > 0) {
           auto i = commandMap.find(cmd);

           (i->second)->execute(mult);
           if (grid->isOver()) break;


           cout << *grid;
        }


    }


    cout << "GAME OVER YOU LOSER" << endl;
}

Interpreter::~Interpreter() {}

    
    




