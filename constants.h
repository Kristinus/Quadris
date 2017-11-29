
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "info.h"
#include <map>

const int GRID_H = 18;
const int GRID_W = 11;
std::map<BlockType, char> BLOCK_MAP = {
	{ BlockType::I, 'I' },
	{ BlockType::J, 'J' },
	{ BlockType::L, 'L' },
	{ BlockType::J, 'O' },
	{ BlockType::J, 'S' },
	{ BlockType::J, 'T' },
	{ BlockType::J, 'Z' }
};

#endif
