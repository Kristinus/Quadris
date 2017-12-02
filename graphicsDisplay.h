#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "info.h"
#include "observer.h"
#include "window.h"
class Grid;
class Score;

class GraphicsDisplay: public Observer<Info> {
  Grid *grid;
  const int gridSize, winSize, cellSize;
  Xwindow xw;
  Score *score;

 public:
  GraphicsDisplay();
  void setGrid(Grid *);

  void notify(Subject<Info> &whoNotified) override;
};
#endif
