#ifndef GRID_H
#define GRID_H
#include <vector>
#include "textDisplay.h"
#include "cell.h"
#include "level.h"

template <typename InfoType> class Observer;

class Grid {
  std::vector<std::vector<Cell>> theGrid;
  Level *theLevel;
  Score* theScore;
  std::vector<Block *> setBlocks;
  Block *currentBlock = nullptr;
  Block *nextBlock = nullptr;
  TextDisplay *td;
  Observer<Info> *ob;
 
  bool isValidMove(std::vector<Cell>, int, int);
public:
  Grid();
  std::vector<Cell> getGridCells();
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

