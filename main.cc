#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
#include "graphicsdisplay.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  Colour current = Colour::Black;
  GraphicsDisplay *gd;

  try {
  while (true) {
    cin >> cmd;
    if (cmd == "new") {
      int n;
      cin >> n;
      gd = new GraphicsDisplay(n, 500);
      g.setObserver(gd);
      g.init(n);
      current = Colour::Black;
      cout << g;
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      try {
        g.setPiece(r, c, current);
        cout << g;
        if(current==Colour::Black) current = Colour::White;
        else current = Colour::Black;
        if(g.isFull()) break;
      } catch (InvalidMove &x) {}
    }
  }
  Colour winner = g.whoWon();
  if(winner==Colour::White) cout << "White wins!" << endl;
  else if(winner==Colour::Black) cout << "Black wins!" << endl;
  else cout << "Tie!" << endl;
  delete gd;
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
