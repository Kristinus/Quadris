#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include <vector>
#include "info.h"
#include "observer.h"
#include "window.h"

class Interpreter;

class GraphicsDisplay: public Observer<Info> {
  const int gridSize, winSize, cellSize, border, colouredSize, x_offset, y_offset;
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
