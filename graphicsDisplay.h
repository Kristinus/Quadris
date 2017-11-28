#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "info.h"
#include "observer.h"
#include "window.h"
class Cell;

class GraphicsDisplay: public Observer<Info> {
  const int gridSize, winSize;
  Xwindow xw;

 public:
  GraphicsDisplay(int winSize);

  void notify(Subject<Info> &whoNotified) override;
};
#endif
