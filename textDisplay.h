#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "info.h"
#include "subject.h"
#include "constants.h"
class Block;

class TextDisplay: public Observer<Info> {
  std::vector<std::vector<char>> theDisplay;
  const std::map<BlockType, char> dict;
  int level;
  int score = 0;
  int hiScore = 0;
  Block *nextBlock;

  void createDict();
 public:
  TextDisplay(int n);

  void notify(Subject<Info> &whoNotified) override;
  void update(int, int int, Block *);

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
