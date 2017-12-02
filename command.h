#ifndef __COMMAND_H__
#define __COMMAND_H__
#include <string>
class Grid;

class Command {
protected:
	Grid *grid;
public:
	Command(Grid *);
	virtual void execute(int mult, std::string) = 0;
	~Command();
};

#endif 
