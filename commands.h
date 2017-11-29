#ifndef __COMMANDS_H
#define __COMMANDS_H
#include "command.h"

class LeftCommand: public Command {
public:
	void execute(int m=1) override;
};

class RightCommand: public Command {
public:
	void execute(int m=1) override;
};

class DownCommand: public Command {
public:
	void execute(int m=1) override;
};

class ClockwiseCommand: public Command {
public:
	void execute(int m=1) override;
};

class CounterClockwiseCommand: public Command {

public:
	void execute(int m=1) override;
};

class DropCommand: public Command {
public:
	void execute(int m=1) override;
};

class LevelUpCommand: public Command {
public:
	void execute(int m=1) override;
};

class LevelDownCommand: public Command {
public:
	void execute(int m=1) override;
};

class NoRandomCommand: public Command {
public:
	void execute(int m=1) override;
};

class RandomCommand: public Command {
public:
	void execute(int m = 1) override;
};

class SequenceCommand: public Command {
public:
	void execute(int m = 1) override;
};

class RestartCommand: public Command {
public:
	void execute(int m=1) override;
};

class HintCommand: public Command {
public:
	void execute(int m=1) override;
};

class ICommand: public Command {
public:
	void execute(int m=1) override;
};

class JCommand: public Command {
public:
	void execute(int m=1) override;
};

class LCommand: public Command {
public:
	void execute(int m=1) override;
};
class TCommand: public Command {
public:
	void execute(int m=1) override;
};
class OCommand: public Command {
public:
	void execute(int m=1) override;
};
class SCommand: public Command {
public:
	void execute(int m=1) override;
};
class ZCommand: public Command {
public:
	void execute(int m=1) override;
};

#endif

