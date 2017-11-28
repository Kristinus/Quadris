#include <iostream>
#include "graphicsDisplay.h"
#include "subject.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int winSize):
 gridSize{11}, winSize{winSize}, xw{winSize, winSize} {
  xw.fillRectangle(0, 0, winSize, winSize, Xwindow::White);
}


void GraphicsDisplay::notify(Subject<Info> &whoNotified) {
  auto info = whoNotified.getInfo();
  int cellSize = winSize / gridSize;
  if(info.block == BlockType::I)
    xw.fillRectangle(info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Cyan);
  else if(info.block == BlockType::J)
    xw.fillRectangle(info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Blue);
  else if(info.block == BlockType::L)
    xw.fillRectangle(info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Orange);
  else if(info.block == BlockType::O)
    xw.fillRectangle(info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Yellow);
  else if(info.block == BlockType::S)
    xw.fillRectangle(info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Green);
  else if(info.block == BlockType::T)
    xw.fillRectangle(info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Magenta);
  else if(info.block == BlockType::Z)
    xw.fillRectangle(info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Red);
}
