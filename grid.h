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
  Block *hintBlock = nullptr;
  Block *nextBlock = nullptr;
  TextDisplay *td;
  Observer<Info> *ob;
  bool isRandom;
 
  bool isValidMove(int, int);
  void attachGridToBlock(Block *);
  int countCompleteLines();
  bool isFilled(std::vector<Cell>);
  void setBlock(Block *);
  void unsetBlock(Block *);
  void updateCells();
  double calculateSmoothness();
  double getAverageHeights(std::vector<int> v);
  double getStandardDeviationHeights(std::vector<int> v);
  std::vector<int> getHeights();
  int countHoles();
  void moveTo(int, int, Block*);
public:
  Grid(Observer<Info> *);
  std::vector<std::vector<Cell>> getGridCells();
  Block *getNextBlock();
  Score *getScore();
  int getLevel();
  void initGrid();
  bool isOver();
  void deleteRow();
  void deleteCurrentBlock();
  void left(int);
  void right(int);
  void down(int);
  void drop();
  void restart();
  void rotateCW(int);
  void rotateCCW(int);
  void levelUp(int);
  void levelDown(int);
  void random(bool);
  void hint();
  void playBlock(Block *);

  friend std::ostream &operator<<(std::ostream &out, Grid &grid);
};



#endif

