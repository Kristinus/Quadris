
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "info.h"
#include <map>

struct Constants {
    const int GRID_H = 18;
    const int GRID_W = 11;
	std::map<BlockType, char> my_map = {
	    { BlockType::L, 'L' },
	    { BlockType::O, 'O' },
	    { BlockType::I, 'I' }
	};
};



#endif
