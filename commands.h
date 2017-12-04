#ifndef __COMMANDS_H
#define __COMMANDS_H

#include "command.h"
#include <fstream>

class Interpreter;

class LeftCommand: public Command {
public:
	LeftCommand(Grid *);
	void execute(int m, std::string) override;
};


class RightCommand: public Command {
public:
	RightCommand(Grid *);
	void execute(int m, std::string) override;
};


class DownCommand: public Command {
public:
	DownCommand(Grid *);
	void execute(int m, std::string) override;
};


class ClockwiseCommand: public Command {
public:
	ClockwiseCommand(Grid *);
	void execute(int m, std::string) override;
};


class CounterClockwiseCommand: public Command {
public:
	CounterClockwiseCommand(Grid *);
	void execute(int m, std::string) override;
};


class DropCommand: public Command {
public:
	DropCommand(Grid *);
	void execute(int m, std::string) override;
};


class LevelUpCommand: public Command {
public:
	LevelUpCommand(Grid *);
	void execute(int m, std::string) override;
};


class LevelDownCommand: public Command {
public:
	LevelDownCommand(Grid *);
	void execute(int m, std::string) override;
};


class NoRandomCommand: public Command {
public:
	NoRandomCommand(Grid *);
	void execute(int m, std::string) override;
};


class RandomCommand: public Command {
public:
	RandomCommand(Grid *);
	void execute(int m, std::string) override;
};


class SequenceCommand: public Command {
	Interpreter *i;
public:
	SequenceCommand(Grid *, Interpreter *);
	void execute(int m, std::string) override;
};


class RestartCommand: public Command {
public:
	RestartCommand(Grid *);
	void execute(int m, std::string) override;
};


class HintCommand: public Command {
public:
	HintCommand(Grid *);
	void execute(int m, std::string) override;
};


class ReplaceCommand: public Command {
	char type;

public:
	ReplaceCommand(Grid *, char);
	void execute(int m, std::string) override;
};

#endif

