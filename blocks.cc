#include "blocks.h"

LBlock::LBlock(int col, int row, bool isHeavy, int level, std::vector<Cell> cells): Block{col, row, isHeavy, level, cells} {}

LBlock::LBlock(bool isHeavy, int level, std::vector<Cell> cells): Block{isHeavy, level, cells} {}

LBlock~LBlock() {}

void LBlock::clockwise() {
   
}

void LBlock::counterclockwise() {

}

