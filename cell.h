#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "info.h"
class Cell: public Subject<Info> {
   Info info;

   public:
   Cell(Info info);
   void setBlock(BlockType block);
   void setState(StateType state);
   void setCoords(size_t, size_t);
   Info getInfo() const;
}

#endif
