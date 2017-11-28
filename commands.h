#ifndef __COMMANDS_H
#define __COMMANDS_H


class SequenceCommand:: public Command {
public:
	void execute(int m = 1);
}

class RandomCommand:: public Command {
public:
	void execute(int m = 1);
}

#endif

