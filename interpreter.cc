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

Interpreter::Interpreter(string seed, bool textOnly, string scriptFile, int startLevel) {
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
	std::map<string, Command*> map = initCommandMap();
    string s;
    while(*in >> s) {
        ProcessedInput processedCommand = parseCommand(s);
        string cmd = processedCommand.command;
        int mult = processedCommand.multiplier;
        if (cmd == "quit") {
        	break;
        }

        if (map.count(cmd)) {
           auto i = map.find(c);
           (i->second)->execute(mult);

        } 
    }
}


void initCommandMap() {
    map<string, Command *> map;
    map["left"] = new LeftCommand();
    map["right"] = new RightCommand();
    map["down"] = new DownCommand();
    map["levelup"] = new LevelUpCommand();
    map["leveldown"] = new LevelDownCommand();
    map["norandom"] = new NoRandomCommand();
    map["sequence"] = new SequenceCommand();
    map["clockwise"] = new ClockwiseCommand();
    map["counterclockwise"] = new counterclockwiseCommand();
    map["drop"] = new DropCommand();
    map["restart"] = new RestartCommand();
    map["I"] = new ICommand();
    map["J"] = new JCommand();
    map["L"] = new LCommand();
    map["O"] = new OCommand();
    map["T"] = new TCommand();
    map["Z"] = new ZCommand();
    map["S"] = new SCommand();
    return map;
}


    
    while(1) {
        string c;
        cin >> c;
        if(map.count(c)) {
            auto i = map.find(c);
            (*i->second).execute();
        } 
    }
}



