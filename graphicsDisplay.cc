#include <iostream>
#include "graphicsDisplay.h"
#include "subject.h"
#include "grid.h"
#include "score.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay():
 gridSize{11}, winSize{600}, xw{600, 600} {
  xw.fillRectangle(0, 0, winSize, winSize, Xwindow::White);
  xw.drawString(10,10,"Level:");
  xw.drawString(10,20,"Score:");
  xw.drawString(10,30,"Hi Score:"); 
  
}

void GraphicsDisplay::setGrid(Grid *grid) {
  this->grid = grid;
  score = grid->getScore();
  xw.drawString(100,10,std::to_string(grid->getLevel()));
  xw.drawString(100,20,std::to_string(score->getCurrentScore()));
  xw.drawString(100,30,std::to_string(score->getHighScore()));
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
