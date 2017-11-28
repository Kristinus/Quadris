<<<<<<< HEAD
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "level.h"
#include "block.h"
#include "grid.h"
#include "graphicsdisplay.h"
#include "interpreterimpl.h"
#include "window.h"
#include "interpreter.h"
using namespace std;

struct ProcessedInput {
	int multiplier;
	string command;
};

Interpreter::Interpreter(string seed, bool textOnly, string scriptFile, int startLevel) {
	if (textOnly == false) {
		gd = new GraphicsDisplay(500);
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
     
    for(int i = commands.size() - 1; i >= 0; i--) {

        string possibleCommand = commands[i];
        int partialCommandLen = cmd.length();
        if (cmd != possibleCommand(0, partialCommandLen)) {
        	possibleCommands.erase(possibleCommands.begin() + i);
        }

    }

    if (commands.size() == 0) {
        	// throw an error
    }

    else if (commands.size() > 1) {
    	// throw an error: ambigious command
    }

    else {
    	cmd = possibleCommands[0];
    }

	istringstream iss{bd};
	iss >> res; // throw an exception
	return ProcessedInput(res, cmd);

}

void Interpreter::run(){

    string s;
    while(*in >> s) {
        ProcessedInput processedCommand = parseCommand(s);
        string cmd = processedCommand.command;
        int mult = processedCommand.multiplier;


        // Command *c;
        // Block *currentBlock;

        // parse command // get the integer if there is an integer

        for (int i = 0; i < mult; i++) {

        	// the Grid calls left // the Grid calls right


        	getKey(hasmah, "left")
        	m.find(cmd).execute();

	        // if (cmd == "left") c = new LeftCommand();
	        // else if (cmd == "right") c = new RightCommand();
	        // else if (cmd == "down") c = new DownCommand();
		    // else if(c == "clockwise") c = new CWCommand();
		    // else if(c == "counterclockwise") c = new CCWCommand();
		    // else if(c == "drop") c = new DropCommand();
		    // else if(c == "levelup") c = new LevelUpCommand();  
		    // else if(c == "leveldown") c = new LevelDownCommand();
		    // else if(c == "norandom") c = new LevelDownCommand();
		    // else if(c == "random") c = new RandomCommand();
		    // else if(c == "restart") c = new RestartCommand();
		    // else if(c == "hint") c = new LevelDownCommand();
		    // else if(c.length() == 1) c = new ReplaceBlock();
	        // if (c == "quit")
	        //     break;
	        // c->execute(currentBlock, m);
	    }
    }
}

