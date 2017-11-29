#include "textDisplay.h"
#include "constants.h"

void TextDisplay::createDict() {
  dict[BlockType::I] = 'I';
  dict[BlockType::J] = 'J';
  dict[BlockType::L] = 'L';
  dict[BlockType::O] = 'O';
  dict[BlockType::S] = 'S';
  dict[BlockType::T] = 'T';
  dict[BlockType::Z] = 'Z';
}

TextDisplay::TextDisplay(Grid *grid): 
  theDisplay{std::vector<std::vector<char>>(18, std::vector<char>(11, '-'))}, grid{grid} {
      createDict();
}

void TextDisplay::notify(Subject<Info> &whoNotified) {
  Info i = whoNotified.getInfo();
  char c = ' ';
  if(dict.count(i.block)) {
    c = dict[i.block];
  } 
  theDisplay[i.row][i.col] = c;
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  //Outputs the scoreboard
  // out << "Level:\t\t" << td.score->level << std::endl;
  // out << "Score:\t\t" << td.score->score << std::endl;
  // out << "Hi Score\t\t" << td.score->hiScore << std::endl;
  out << "-----------" << std::endl;

  //Outputs the Grid
  for(int r=td.theDisplay.size(); r>=0; r--) {
    for(auto c:td.theDisplay[r]) {
      out << c;
    }
    out << std::endl;
  }

  //Outputs Next Block
  out << "-----------" << std::endl;
  out << "Next:" << std::endl;
  // out << *(td.nextBlock) << std::endl;

  return out;
}
