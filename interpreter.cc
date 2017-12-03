#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "level.h"
#include <memory>
#include "block.h"
#include "grid.h"
#include "commands.h"
#include "graphicsDisplay.h"
#include "constants.h"
#include "interpreter.h"
#include "invalidinputexception.h"
using namespace std;

struct ProcessedInput {
	string command;
	int multiplier;
	string file;
};

void Interpreter::initCommandMap() {
	commandMap["left"] = std::make_unique<LeftCommand>(grid);
	commandMap["right"] = std::make_unique<RightCommand>(grid);
	commandMap["down"] = std::make_unique<DownCommand>(grid);
	commandMap["levelup"] = std::make_unique<LevelUpCommand>(grid);
	commandMap["leveldown"] = std::make_unique<LevelDownCommand>(grid);
	commandMap["norandom"] = std::make_unique<NoRandomCommand>(grid);
	commandMap["sequence"] = std::make_unique<SequenceCommand>(grid, this);
	commandMap["clockwise"] = std::make_unique<ClockwiseCommand>(grid);
	commandMap["counterclockwise"] = std::make_unique<CounterClockwiseCommand>(grid);
	commandMap["drop"] =  std::make_unique<DropCommand>(grid);
	commandMap["restart"] =  std::make_unique<RestartCommand>(grid);
	commandMap["hint"] =  std::make_unique<HintCommand>(grid);
	commandMap["I"] =  std::make_unique<ReplaceCommand>(grid, 'I');
	commandMap["J"] =  std::make_unique<ReplaceCommand>(grid, 'J');
	commandMap["L"] =  std::make_unique<ReplaceCommand>(grid, 'L');
	commandMap["O"] =  std::make_unique<ReplaceCommand>(grid, 'O');
	commandMap["T"] =  std::make_unique<ReplaceCommand>(grid, 'S');
	commandMap["Z"] =  std::make_unique<ReplaceCommand>(grid, 'T');
	commandMap["S"] =  std::make_unique<ReplaceCommand>(grid, 'Z'); 
}

Interpreter::Interpreter(int seed, bool textOnly, string scriptFile, int startLevel) {
	if (textOnly == false) {
		gd = new GraphicsDisplay();
	}
	grid = new Grid(startLevel, seed, gd, scriptFile);
	if(gd) gd->setGrid(grid);

	initCommandMap();
}

bool isDigit(char c) {
	if ((c >= '0') && (c <= '9')) return true;
	else return false;
}



ProcessedInput Interpreter::parseCommand(std::istream &input, string command) {
	if (command == "") throw InvalidInputException("Invalid Input: No Input Provided.");
	string digits = "";
	string typedCommand;
	string file;
	int res;
	unsigned int i;
	for (i = 0; i < command.length(); i++) {
		if (isDigit(command[i])) {
			digits += command[i];
		} else {
			break;
		}
	}

	vector<string> possibleCommands {"left", "right", "down", "levelup", "leveldown", 
	"norandom", "random", "sequence", "clockwise", "counterclockwise", "drop", "restart", 
	"hint", "I", "J", "L", "O", "S", "Z", "T", "quit",};

	int pos = command.find(' ');
	typedCommand = command.substr(i, pos-i);
    // file = command.substr(pos);

   	// filter list of possible Commands by comparing the 
   	// prefixes with typed command
	for (int i = possibleCommands.size() - 1; i >= 0; i--) {
		string possibleCommand = possibleCommands[i];
		int partialCommandLen = typedCommand.length();
		if (typedCommand != possibleCommand.substr(0, partialCommandLen)) {
			possibleCommands.erase(possibleCommands.begin() + i);
		}
	}

    // case if no commands share the prefix as the typed command
	if (possibleCommands.size() == 0) {

		throw InvalidInputException("Invalid Input: Not a Possible Command.");
	}

    // case if more than one command matches the typed prefix
	else if (possibleCommands.size() > 1) {
		throw InvalidInputException("Invalid Input: Input is Ambiguous.");
	}

    // only one command matches the typed prefix. This is the command
    // that we execute
	else {
		typedCommand = possibleCommands[0];
	}

	if (typedCommand == "norandom" || typedCommand == "sequence") {
		input >> file;
	}

    // if a number was
	if (digits != "") {
		istringstream iss{digits};
		iss >> res; 
		return ProcessedInput{possibleCommands[0], res, file};
	}
	else return ProcessedInput{possibleCommands[0], 1, file};

}

void Interpreter::run() {
	cout << *grid;
	run(*in);

}

void Interpreter::run(std::istream &in) {
	string s;
	while(in >> s) {
		ProcessedInput processedInput;
		try {
			// parse command for digits and string command
			processedInput = parseCommand(in, s);
		} catch (InvalidInputException e) {
        	//cout << e.message << endl;
			continue;
		}
		string cmd = processedInput.command;
		int mult = processedInput.multiplier;
		if (cmd == "quit") {
			break;
		}

		if (commandMap.count(cmd) > 0) {
			auto i = commandMap.find(cmd);
			(i->second)->execute(mult, processedInput.file);
			if (grid->isOver()) {
				cout << "GAME OVER YOU LOSER" << endl;           
				gameOver = true;
			}
			else if (cmd != "sequence")
				cout << *grid;
		}
		
		if (gameOver) {
			cout << "Wanna play again? [yes/no]" << endl;
			in >> s;

			if (s == "yes" || s == "Y" || s == "y") {

				// get the restart Command object and execute it
				(commandMap.find("restart")->second)->execute(1,"");
				gameOver = false;
				cout << *grid;
			}
			else break;
		}
	}
}


Interpreter::~Interpreter() {}







