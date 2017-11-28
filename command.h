#ifndef __COMMAND_H__
#define __COMMAND_H__

class Command {


public:
	virtual void execute(int mult = 1) = 0;
	~Command();
	Command();
}

#endif 
