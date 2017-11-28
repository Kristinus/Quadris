
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "info.h"
#include <map>

const int GRID_H = 18;
const int GRID_W = 11;
std::map<BlockType, char> BLOCK_MAP = {
	{ BlockType::L, 'L' },
	{ BlockType::O, 'O' },
	{ BlockType::I, 'I' }
};

#endif
