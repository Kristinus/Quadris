#ifndef GRID_H
#define GRID_H
#include <vector>
#include "textDisplay.h"
#include "cell.h"
#include "level.h"
#include "blocks.h"


class Grid {
   std::vector<std::vector<Cell>> theGrid;
   Level *theLevel;
   std::vector<Block *> setBlocks;
   Block *currentBlock;
   Block *nextBlock;
 //  TextDisplay *td;
 //  GraphicsDisplay *gd;
   
   public:
   void initGrid();
   bool isOver();
   void deleteRow();
   void left(int);
   void right(int);
   void down(int);
   void drop(int);
   void restart();
   void rotateCW(int);
   void rotateCCW(int);
   void levelUp(int);
   void levelDown(int);
   void random();
   void hint();
};
#endif

