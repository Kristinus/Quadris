#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include <map>
#include "observer.h"
#include "score.h"
#include "info.h"
#include "subject.h"
class Block;

class TextDisplay: public Observer<Info> {
  std::vector<std::vector<char>> theDisplay;
  std::map<BlockType, char> dict;
  Score *score;
  Block *nextBlock;

  void createDict();
 public:
  TextDisplay();

  void notify(Subject<Info> &whoNotified) override;
  void update(Score *, Block *);

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
