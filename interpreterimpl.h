#ifndef __INTERPRETER_IMPL_H__
#define __INTERPRETER_IMPL_H__

#include <map>
#include <vector>
#include <string>
#include <memory>
#include "commands.h"

struct InterpreterImpl {
	std::vector<std::string> possibleCommands {"left", "right", "down", "levelup", "leveldown", 
	"norandom", "random", "sequence", "clockwise", "counterclockwise", "drop", "restart", 
	"hint", "I", "J", "L", "O", "S", "Z", "T", "quit"};

	void initKeyMap(std::map<std::string, std::string> &keyMap) {
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

	void initCommandMap(std::map<std::string, std::shared_ptr<Command>> &commandMap, Grid * grid, Interpreter * interpreterptr) {
	    commandMap["left"] = std::make_unique<LeftCommand>(grid);
	    commandMap["right"] = std::make_unique<RightCommand>(grid);
	    commandMap["down"] = std::make_unique<DownCommand>(grid);
	    commandMap["levelup"] = std::make_unique<LevelUpCommand>(grid);
	    commandMap["leveldown"] = std::make_unique<LevelDownCommand>(grid);
	    commandMap["norandom"] = std::make_unique<NoRandomCommand>(grid);
	    commandMap["random"] = std::make_unique<RandomCommand>(grid);
	    commandMap["sequence"] = std::make_unique<SequenceCommand>(grid, interpreterptr);
	    commandMap["clockwise"] = std::make_unique<ClockwiseCommand>(grid);
	    commandMap["counterclockwise"] = std::make_unique<CounterClockwiseCommand>(grid);
	    commandMap["drop"] =  std::make_unique<DropCommand>(grid);
	    commandMap["restart"] =  std::make_unique<RestartCommand>(grid);
	    commandMap["hint"] =  std::make_unique<HintCommand>(grid);
	    commandMap["I"] =  std::make_unique<ReplaceCommand>(grid, 'I');
	    commandMap["J"] =  std::make_unique<ReplaceCommand>(grid, 'J');
	    commandMap["L"] =  std::make_unique<ReplaceCommand>(grid, 'L');
	    commandMap["O"] =  std::make_unique<ReplaceCommand>(grid, 'O');
	    commandMap["S"] =  std::make_unique<ReplaceCommand>(grid, 'S');
	    commandMap["T"] =  std::make_unique<ReplaceCommand>(grid, 'T');
	    commandMap["Z"] =  std::make_unique<ReplaceCommand>(grid, 'Z'); 
	}

};

#endif
