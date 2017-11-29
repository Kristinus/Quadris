#ifndef __COMMAND_H__
#define __COMMAND_H__
class Grid;

class Command {
protected:
	Grid *grid;
public:
	Command(Grid *);
	virtual void execute(int mult = 1) = 0;
	~Command();
};

#endif 
