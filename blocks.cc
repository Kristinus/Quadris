#include "blocks.h"

Block::Block(int x, int y, bool isHeavy): x{x}, y{y}, isHeavy{isHeavy} {

}

IBlock::IBlock(int x, int y, bool isHeavy):Block(x, y, isHeavy) {

}


OBlock::IBlock(int x, int y, bool isHeavy):Block(x, y, isHeavy) {

}


ZBlock::IBlock(int x, int y, bool isHeavy):Block(x, y, isHeavy) {

}

SBlock::IBlock(int x, int y, bool isHeavy):Block(x, y, isHeavy) {

}

LBlock::IBlock(int x, int y, bool isHeavy):Block(x, y, isHeavy) {

}

TBlock::IBlock(int x, int y, bool isHeavy):Block(x, y, isHeavy) {

}

IBlock::IBlock(int x, int y, bool isHeavy):Block(x, y, isHeavy) {

}
