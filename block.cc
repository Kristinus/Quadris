#include "block.h"

using namespace std;

Block::Block(int col, int row, bool isHeavy, vector<Cell> cells): cells{cells}, isHeavy{isHeavy}, level{level}, col{col}, row{row} {}

Block::~Block(){
   cells.clear();
}

vector<Cell> Block::getBlockCells() {
   return cells;
}

bool Block::isBlockHeavy(){
   return isHeavy;
}

int Block::getLevel(){
   return level;
}

void Block::left(){
   col--;
   for(auto n : cells) {
      Info i = n.getInfo();
      size_t c = i.col - 1;
      n.setCoords(i.row, c);
   }
}

void Block::right(){
   col++;
   for(auto n: cells){
      Info i = n.getInfo();
      size_t c = i.col + 1;
      n.setCoords(i.row, c);
   }
}

void Block::down(){
   row--;
   for(auto n: cells) {
      Info i = n.getInfo();
      size_t r = i.row - 1;
      n.setCoords(r, i.col);
   }
}

