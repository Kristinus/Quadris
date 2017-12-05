#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "level.h"
#include <memory>
#include "commands.h"
#include "observer.h"
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
    commandMap["left"] = std::make_unique<LeftCommand>(grid.get());
    commandMap["right"] = std::make_unique<RightCommand>(grid.get());
    commandMap["down"] = std::make_unique<DownCommand>(grid.get());
    commandMap["levelup"] = std::make_unique<LevelUpCommand>(grid.get());
    commandMap["leveldown"] = std::make_unique<LevelDownCommand>(grid.get());
    commandMap["norandom"] = std::make_unique<NoRandomCommand>(grid.get());
    commandMap["random"] = std::make_unique<RandomCommand>(grid.get());
    commandMap["sequence"] = std::make_unique<SequenceCommand>(grid.get(), this);
    commandMap["clockwise"] = std::make_unique<ClockwiseCommand>(grid.get());
    commandMap["counterclockwise"] = std::make_unique<CounterClockwiseCommand>(grid.get());
    commandMap["drop"] =  std::make_unique<DropCommand>(grid.get());
    commandMap["restart"] =  std::make_unique<RestartCommand>(grid.get());
    commandMap["hint"] =  std::make_unique<HintCommand>(grid.get());
    commandMap["I"] =  std::make_unique<ReplaceCommand>(grid.get(), 'I');
    commandMap["J"] =  std::make_unique<ReplaceCommand>(grid.get(), 'J');
    commandMap["L"] =  std::make_unique<ReplaceCommand>(grid.get(), 'L');
    commandMap["O"] =  std::make_unique<ReplaceCommand>(grid.get(), 'O');
    commandMap["S"] =  std::make_unique<ReplaceCommand>(grid.get(), 'S');
    commandMap["T"] =  std::make_unique<ReplaceCommand>(grid.get(), 'T');
    commandMap["Z"] =  std::make_unique<ReplaceCommand>(grid.get(), 'Z'); 
}


void Interpreter::initKeyMap() {
    keyMap["Q"] = "left";
    keyMap["S"] = "right";
    keyMap["T"] = "down";
    keyMap["u"] = "levelup";
    keyMap["i"] = "leveldown";
    keyMap["R"] = "clockwise";
    keyMap["space"] = "drop";
    keyMap["r"] = "restart";
    keyMap["h"] = "hint";
}


Interpreter::Interpreter(int seed, std::shared_ptr<Observer<Info>> ob, string scriptFile, int startLevel) {
	grid = std::make_unique<Grid>(startLevel, seed, ob.get(), scriptFile);

	initCommandMap();
   	initKeyMap();
}

// Checks if character is a valid integer digit
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

	vector<string> possibleCommands = constants::possibleCommands;

	int pos = command.find(' ');
	typedCommand = command.substr(i, pos-i);

   	// Filter list of possible Commands by comparing the 
   	// prefixes with typed command
	for (int i = possibleCommands.size() - 1; i >= 0; i--) {
		string possibleCommand = possibleCommands[i];
		int partialCommandLen = typedCommand.length();
		
      if (typedCommand != possibleCommand.substr(0, partialCommandLen)) {
			possibleCommands.erase(possibleCommands.begin() + i);
		}
	}

   // Case if no commands share the prefix as the typed command
	if (possibleCommands.size() == 0) {
		throw InvalidInputException("Invalid Input: Not a Possible Command.");
	}

   // Case if more than one command matches the typed prefix
	else if (possibleCommands.size() > 1) {
		throw InvalidInputException("Invalid Input: Input is Ambiguous.");
	}

   // Only one command matches the typed prefix. This is the command
   // that we execute
	else {
		typedCommand = possibleCommands[0];
	}

	if (typedCommand == "norandom" || typedCommand == "sequence") {
		input >> file;
	}

   // If a number was
	if (digits != "") {
		istringstream iss{digits};
		iss >> res; 
		return ProcessedInput{possibleCommands[0], res, file};
	}
	else return ProcessedInput{possibleCommands[0], 1, file};
}


void Interpreter::run() {
	cout << *grid;
	run(cin);
}


std::istream &Interpreter::run(std::istream &in) {
	string s;

	while(in >> s) {
		ProcessedInput processedInput;

		try {
			// Parse command for digits and string command
			processedInput = parseCommand(in, s);
		} catch (InvalidInputException e) {
			continue;
		}

		string cmd = processedInput.command;
		int mult = processedInput.multiplier;
		
      if (cmd == "quit") {
			break;
		}

		if (commandMap.count(cmd) > 0) {
			commandMap.find(cmd)->second->execute(mult, processedInput.file);
			
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
				// Get the restart Command object and execute it
				(commandMap.find("restart")->second)->execute(1,"");
				gameOver = false;
				cout << *grid;
			}
			else break;
	   }
	}
   return in;
}


// BONUS FEATURE - Key Presses
bool Interpreter::run(std::string key) {
    if (key == "q") {
        return false;
    }

    if (keyMap.count(key) > 0) {
        auto cmd = (keyMap.find(key))->second;
        commandMap.find(cmd)->second->execute(1, "");
        
        if (grid->isOver()) {
            cout << "GAME OVER YOU LOSER" << endl;
            cout << "Press [y] to restart" << endl;
            return false;
        }
    }
    return true;
}


// Restarts Game
bool Interpreter::reset(std::string key) {
    if (key == "y") {
        // Get the restart Command object and execute it
        (commandMap.find("restart")->second)->execute(1,"");
        cout << *grid;
        return true;
    }
    return false;
}


void Interpreter::operator()() {
    run();
}

