#ifndef GRID_H
#define GRID_H
#include <vector>
#include "textDisplay.h"
#include "cell.h"
#include "level.h"
class Grid {
   vector<vector<Cell>> theGrid;
   TextDisplay *td;
   GraphicsDisplay *gd;
   
   public:
   bool isOver();
   void deleteRow();
   void left();
   void right();
   void down();
   void drop();
   void restart();
   void rotateCW();
   void rotateCCW();
   void levelUp();
   void levelDown();
   void random();
   void hint();
}
#endif
