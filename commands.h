#ifndef __COMMANDS_H
#define __COMMANDS_H
#include "command.h"

class LeftCommand: public Command {
public:
	LeftCommand(Grid *);
	void execute(int m=1) override;
};

class RightCommand: public Command {
public:
	RightCommand(Grid *);
	void execute(int m=1) override;
};

class DownCommand: public Command {
public:
	DownCommand(Grid *);
	void execute(int m=1) override;
};

class ClockwiseCommand: public Command {
public:
	ClockwiseCommand(Grid *);
	void execute(int m=1) override;
};

class CounterClockwiseCommand: public Command {

public:
	CounterClockwiseCommand(Grid *);
	void execute(int m=1) override;
};

class DropCommand: public Command {
public:
	DropCommand(Grid *);
	void execute(int m=1) override;
};

class LevelUpCommand: public Command {
public:
	LevelUpCommand(Grid *);
	void execute(int m=1) override;
};

class LevelDownCommand: public Command {
public:
	LevelDownCommand(Grid *);
	void execute(int m=1) override;
};

class NoRandomCommand: public Command {
public:
	NoRandomCommand(Grid *);
	void execute(int m=1) override;
};

class RandomCommand: public Command {
public:
	RandomCommand(Grid *);
	void execute(int m = 1) override;
};

class SequenceCommand: public Command {
public:
	SequenceCommand(Grid *);
	void execute(int m = 1) override;
};

class RestartCommand: public Command {
public:
	RestartCommand(Grid *);
	void execute(int m=1) override;
};

class HintCommand: public Command {
public:
	HintCommand(Grid *);
	void execute(int m=1) override;
};

class ICommand: public Command {
public:
	ICommand(Grid *);
	void execute(int m=1) override;
};

class JCommand: public Command {
public:
	JCommand(Grid *);
	void execute(int m=1) override;
};

class LCommand: public Command {
public:
	LCommand(Grid *);
	void execute(int m=1) override;
};
class TCommand: public Command {
public:
	TCommand(Grid *);
	void execute(int m=1) override;
};
class OCommand: public Command {
public:
	OCommand(Grid *);
	void execute(int m=1) override;
};
class SCommand: public Command {
public:
	SCommand(Grid *);
	void execute(int m=1) override;
};
class ZCommand: public Command {
public:
	ZCommand(Grid *);
	void execute(int m=1) override;
};

#endif

