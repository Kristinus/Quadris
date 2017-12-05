#include "graphicsDisplay.h"
#include "subject.h"
#include "interpreter.h"
#include "constants.h"
#include <unistd.h>

using namespace std;

GraphicsDisplay::GraphicsDisplay():
  gridSize{constants::GRID_HEIGHT}, winSize{600}, cellSize{winSize/gridSize}, border{1}, colouredSize{cellSize-border*2},
  x_offset{13*cellSize}, y_offset{50}, xw{650, 650} {
  xw.fillRectangle(0, 0, winSize, winSize, Xwindow::White);
  xw.fillRectangle(constants::GRID_WIDTH * cellSize, 0, 1, 700, Xwindow::Black);
  xw.fillRectangle(0, y_offset + constants::GRID_HEIGHT*cellSize, 650, 10, Xwindow::Black);
  xw.drawString(10,10,"Level:");
  xw.drawString(10,20,"Score:");
  xw.drawString(10,30,"Hi Score:"); 
  xw.drawString(11*cellSize+10,10,"Next:"); 
  xw.drawString(11*cellSize+10,10+cellSize*3,"Hold:"); 
  xw.drawString(winSize-225,winSize+40,"@2017:Bryan Kristiono, Monica Xu, Sarah Zhang"); 
}


// Updates graphics display based on notify call from cell
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
  else if(info.block == BlockType::HINT)
    colour = Xwindow::Black;
  else if(info.block == BlockType::DOT)
    colour = Xwindow::Brown;

  //If nextBlock
  if(info.state == StateType::NEXT)
    xw.fillRectangle(x_offset + info.col * cellSize + border, (1-info.row) * cellSize + border, colouredSize, colouredSize, colour);
  else if(info.state == StateType::HOLD)
    xw.fillRectangle(x_offset + info.col * cellSize + border, (5-info.row) * cellSize, colouredSize, colouredSize, colour);
  else
    xw.fillRectangle(info.col * cellSize, y_offset + (constants::GRID_HEIGHT - 1- info.row) * cellSize, colouredSize, colouredSize, colour);
}


// Clears next block
void GraphicsDisplay::clearNext() {
  xw.fillRectangle(x_offset, 0, cellSize*4, cellSize*8, Xwindow::White);
}


// Clears the board
void GraphicsDisplay::clear() {
  xw.fillRectangle(0, 0, 650, 650, Xwindow::White);
  xw.fillRectangle(11 * cellSize, 0, 1, 700, Xwindow::Black);
  xw.drawString(10,10,"Level:");
  xw.drawString(10,20,"Score:");
  xw.drawString(10,30,"Hi Score:"); 
  xw.drawString(11*cellSize+10,10,"Next:");
  xw.drawString(11*cellSize+10,10+cellSize*3,"Hold:"); 
}


// Updates the level/scores
void GraphicsDisplay::update(int level, int score, int hiScore) {
  xw.fillRectangle(100, 0, 100, 50, Xwindow::White);
  xw.drawString(100,10,std::to_string(level));
  xw.drawString(100,20,std::to_string(score));
  xw.drawString(100,30,std::to_string(hiScore));
}


void GraphicsDisplay::run(Interpreter *i) {
  bool running = true;

  while(running) {
    running = i->run(xw.readInput());
    usleep(100000);
    
    if (!running) {
		  running = i->reset(xw.readInput());
	  } 
  }
}

