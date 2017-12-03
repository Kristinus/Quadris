#include <iostream>
#include "graphicsDisplay.h"
#include "subject.h"
#include "grid.h"
#include "score.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay():
 gridSize{18}, winSize{600}, cellSize{winSize/gridSize}, xw{650, 650} {
  xw.fillRectangle(0, 0, winSize, winSize, Xwindow::White);
  xw.fillRectangle(11 * cellSize, 0, 1, 700, Xwindow::Black);
  xw.drawString(10,10,"Level:");
  xw.drawString(10,20,"Score:");
  xw.drawString(10,30,"Hi Score:"); 
  xw.drawString(11*cellSize+10,10,"Next:"); 
  
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
  int colour = xw.White;

  //Changes colour depending on BlockType
  if(info.block == BlockType::I) 
    colour = Xwindow::Cyan;
  else if(info.block == BlockType::J)
    colour = Xwindow::Blue;
  else if(info.block == BlockType::L)
    colour = Xwindow::Orange;
  else if(info.block == BlockType::O)
    colour = Xwindow::Yellow;
  else if(info.block == BlockType::S)
    colour = Xwindow::Green;
  else if(info.block == BlockType::T)
    colour = Xwindow::Magenta;
  else if(info.block == BlockType::Z)
    colour = Xwindow::Red;
  
  //If nextBlock
  if(info.state == StateType::NEXT) {
    xw.fillRectangle((13+info.col) * cellSize, (1-info.row) * cellSize, cellSize, cellSize, colour);
  } 
  else
    xw.fillRectangle(info.col * cellSize, 50 + (17 - info.row) * cellSize, cellSize, cellSize, colour);
}

void GraphicsDisplay::clearNext() {
  xw.fillRectangle(13 * cellSize, 0, cellSize*4, cellSize*2, Xwindow::White);
}

void GraphicsDisplay::update() {
  xw.fillRectangle(100, 0, 100, 50, Xwindow::White);
  xw.drawString(100,10,std::to_string(grid->getLevel()));
  xw.drawString(100,20,std::to_string(score->getCurrentScore()));
  xw.drawString(100,30,std::to_string(score->getHighScore()));
}

void GraphicsDisplay::clear() {
  xw.fillRectangle(0, 0, 650, 650, Xwindow::White);
  xw.fillRectangle(11 * cellSize, 0, 1, 700, Xwindow::Black);
  xw.drawString(10,10,"Level:");
  xw.drawString(10,20,"Score:");
  xw.drawString(10,30,"Hi Score:"); 
  xw.drawString(11*cellSize+10,10,"Next:"); 
  update();
}
