#include "textdisplay.h"

TextDisplay::TextDisplay(int n): theDisplay{std::vector<std::vector<char>>(n, std::vector<char>(n, '-'))}, gridSize{n} {
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
  Info i = whoNotified.getInfo();
  char c = '-';
  if(i.colour==Colour::Black) c = 'B';
  else if(i.colour==Colour::White) c='W';
  theDisplay[i.row][i.col] = c;
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  for(auto r:td.theDisplay) {
    for(auto c:r) {
      out << c;
    }
    out << std::endl;
  }
  return out;
}
