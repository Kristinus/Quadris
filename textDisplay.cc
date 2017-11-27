#include "textDisplay.h"

TextDisplay::createDict() {
  dict[BlockType::I] = 'I';
  dict[BlockType::J] = 'J';
  dict[BlockType::L] = 'L';
  dict[BlockType::O] = 'O';
  dict[BlockType::S] = 'S';
  dict[BlockType::T] = 'T';
  dict[BlockType::Z] = 'Z';
}

TextDisplay::TextDisplay(Grid &grid): 
  theDisplay{std::vector<std::vector<char>>(n, std::vector<char>(n, '-'))},
  grid{grid} {
      createDict();
}

void TextDisplay::notify(Subject<Info> &whoNotified) {
  Info i = whoNotified.getInfo();
  char c = ' ';
  if(dict.count(i.blockType)) {
    c = dict.find(i.blockType);
  } 
  theDisplay[i.row][i.col] = c;
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  //Outputs the scoreboard
  out << "Level:\t\t" << t.level << std::endl;
  out << "Score:\t\t" << t.score << std::endl;
  out << "Hi Score\t\t" << t.hiScore << std::endl;
  out << "-----------" << std::end;

  //Outputs the Grid
  for(auto r:td.theDisplay) {
    for(auto c:r) {
      out << c;
    }
    out << std::endl;
  }

  //Outputs Next Block
  out << "-----------" << std::end;
  out << "Next:" << std::endl;
  out << *(t.nextBlock) << std::endl;
}
