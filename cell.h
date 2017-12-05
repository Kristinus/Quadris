#ifndef CELL_H
#define CELL_H

#include "subject.h"
#include "info.h"

class Block;

class Cell: public Subject<Info> {
   Info info;

public:
   Cell(Info &info);
   void setBlock(BlockType block);
   void setState(StateType state);
   void setCoords(unsigned int, unsigned int);
   void moveDown(unsigned int);
   Info getInfo() const;
};

#endif
