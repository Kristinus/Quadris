#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "level.h"
#include "block.h"
#include "grid.h"
#include "commands.h"
#include "interpreter.h"
using namespace std;

struct ProcessedInput {
	int multiplier;
	string command;

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
    commandMap["I"] = new ICommand(grid);
    commandMap["J"] = new JCommand(grid);
    commandMap["L"] = new LCommand(grid);
    commandMap["O"] = new OCommand(grid);
    commandMap["T"] = new TCommand(grid);
    commandMap["Z"] = new ZCommand(grid);
    commandMap["S"] = new SCommand(grid);
}

Interpreter::Interpreter(string seed, bool textOnly, string scriptFile, int startLevel) {
	initCommandMap();
	if (textOnly == false) {
	//	gd = new GraphicsDisplay(500);
	}
	// grid = new Grid(seed, gd, startLevel);
}

bool isDigit(char c) {
	if ((c >= '0') && (c <= '9')) return true;
	else return false;
}

ProcessedInput parseCommand(string command) {
	string bd = "";
	string cmd;
	int res;
	// if (!isDigit(command[i])) return ProcessedInput(1, command);
	size_t i;
	for (i = 0; i < command.length(); i++) {
		if (isDigit(command[i])) {
			bd += command[i];
		} else {
			break;
		}
	}

	vector<string> possibleCommands {"left", "right", "down", "levelup", "leveldown", "norandom", "random", "sequence", "clockwise", "counterclockwise", "drop", "restart", "hint", "I", "J", "L", "O", "S", "Z", "T", "quit",};
    cmd = command.substr(i);
     
    for (int i = possibleCommands.size() - 1; i >= 0; i--) {

        string possibleCommand = possibleCommands[i];
        int partialCommandLen = cmd.length();
        if (cmd != possibleCommand.substr(0, partialCommandLen)) {
        	possibleCommands.erase(possibleCommands.begin() + i);
        }

    }

    if (possibleCommands.size() == 0) {
        	// throw an error
    }

    else if (possibleCommands.size() > 1) {
    	// throw an error: ambigious command
    }

    else {
    	cmd = possibleCommands[0];
    }

	istringstream iss{bd};
	iss >> res; // throw an exception
	return ProcessedInput{res, possibleCommands[0]};

}

void Interpreter::run() {
    string s;
    while(*in >> s) {
        ProcessedInput processedCommand = parseCommand(s);
        string cmd = processedCommand.command;
        int mult = processedCommand.multiplier;
        if (cmd == "quit") {
        	break;
        }

        if (commandMap.count(cmd)) {
           auto i = commandMap.find(cmd);

           (i->second)->execute(mult);
        } 
    }
}



    
    




