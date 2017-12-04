#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include <iostream>
#include <vector>
#include "info.h"
#include <memory>
#include "observer.h"
#include "window.h"

class Interpreter;

class GraphicsDisplay: public Observer<Info> {
  const int gridSize, winSize, cellSize;
  Xwindow xw;

public:
  GraphicsDisplay();
  void notify(Subject<Info> &whoNotified) override;
  void clearNext() override;
  void update(int, int, int) override;
  void clear() override;
  void run(Interpreter *i);
};

#endif
