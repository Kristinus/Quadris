#include "textDisplay.h"
#include "constants.h"
#include <memory>
#include <iostream>

using namespace std;

void TextDisplay::createDict() {
  dict[BlockType::I] = 'I';
  dict[BlockType::J] = 'J';
  dict[BlockType::L] = 'L';
  dict[BlockType::O] = 'O';
  dict[BlockType::S] = 'S';
  dict[BlockType::T] = 'T';
  dict[BlockType::Z] = 'Z';
  dict[BlockType::NONE] = ' ';
  dict[BlockType::HINT] = '?';
  dict[BlockType::DOT] = '*';
}


TextDisplay::TextDisplay(): theDisplay{std::vector<std::vector<char>>(18, std::vector<char>(11, ' '))} {
      createDict();
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
  theDisplay = std::vector<std::vector<char>>(18, std::vector<char>(11, ' '));
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
  for(int r=td.theDisplay.size()-1; r>=0; r--) {
    for(auto c:td.theDisplay[r]) {
      out << c;
    }

    out << std::endl;
  }
  out << "-----------" << std::endl;
  return out;
}

