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
	std::ifstream seq;
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

// class ICommand: public Command {
// public:
// 	ICommand(Grid *);
// 	void execute(int m, std::string) override;
// };

// class JCommand: public Command {
// public:
// 	JCommand(Grid *);
// 	void execute(int m, std::string) override;
// };

// class LCommand: public Command {
// public:
// 	LCommand(Grid *);
// 	void execute(int m, std::string) override;
// };
// class TCommand: public Command {
// public:
// 	TCommand(Grid *);
// 	void execute(int m, std::string) override;
// };
// class OCommand: public Command {
// public:
// 	OCommand(Grid *);
// 	void execute(int m, std::string) override;
// };
// class SCommand: public Command {
// public:
// 	SCommand(Grid *);
// 	void execute(int m, std::string) override;
// };
// class ZCommand: public Command {
// public:
// 	ZCommand(Grid *);
// 	void execute(int m, std::string) override;
// };

#endif

