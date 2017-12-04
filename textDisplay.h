#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include <map>
#include "observer.h"
#include "score.h"
#include "info.h"
#include "subject.h"
#include <memory>
class Grid;

class TextDisplay: public Observer<Info> {
  std::vector<std::vector<char>> theDisplay;
  std::map<BlockType, char> dict;
  Grid *grid;
  std::unique_ptr<Score> score;

  void createDict();
 public:
  TextDisplay(Grid *);

  void notify(Subject<Info> &whoNotified) override;
  void clear() override;
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
