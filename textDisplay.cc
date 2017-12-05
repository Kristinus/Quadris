#include "textDisplay.h"
#include "constants.h"
#include <memory>
#include <iostream>

using namespace std;


TextDisplay::TextDisplay(): theDisplay{std::vector<std::vector<char>>
  (constants::GRID_HEIGHT, std::vector<char>(constants::GRID_WIDTH, ' '))} {
      dict = constants::TEXT_DICT;
}


// Updates based on notify call from cell
void TextDisplay::notify(Subject<Info> &whoNotified) {
  Info i = whoNotified.getInfo();
  char c = ' ';

  if(dict.count(i.block) > 0) {
    c = dict[i.block];
  }

  theDisplay[i.row][i.col] = c;
}


// Clears entire display
void TextDisplay::clear() {
  theDisplay.clear();
  theDisplay = std::vector<std::vector<char>>
  (constants::GRID_HEIGHT, std::vector<char>(constants::GRID_WIDTH, ' '));
}


// Updates level/scores
void TextDisplay::update(int level, int score, int hiScore) {
  this->level = level;
  this->score = score;
  this->hiScore = hiScore;
}


std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  //Outputs the scoreboard
  out << "Level:\t\t" << td.level << std::endl;
  out << "Score:\t\t" << td.score << std::endl;
  out << "Hi Score\t" << td.hiScore << std::endl;
  out << "-----------" << std::endl;

  //Outputs the Grid
  for (int r = td.theDisplay.size()-1; r >= 0; r--) {
    for (auto c:td.theDisplay[r]) {
      out << c;
    }

    out << std::endl;
  }
  out << "-----------" << std::endl;
  return out;
}

