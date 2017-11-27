#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// -text runs the program in text only mode (no graphics) defult is ns show both text and graphics
// -seed number, sets the random number generator's seed to xxx
// -screiptfile xxx, use xxx instead of sequence as a source of blocks for level 0
// - startleevl n, starts the game in level n... otherwise default is zero


int main(int argc, char *argv[]) {

  const int MIN_LEVEL = 0;
  const int MAX_LEVEL = 4;

  cin.exceptions(ios::eofbit|ios::failbit);
  bool textOnly = false;
  int seed = 0;
  string scriptFile = "sequence.txt";
  int startLevel = 0;

  for (int i = 1; i < argc; ++i) {
    string cmd = argv[i];

    if (cmd == "-text") {
      textOnly = true;
    }
    else if (cmd == "-seed") {
      if (i + 1 == argc) {
        // there is no seed argument
      }
      else {
        // make sure it sucessful converts to int
        istringstream iss{argv[i+1]};
        if (!(iss >> seed)) {
          cerr << "seed is not number" << endl;
          return 1;
        }
        i++;
        
      }
    }
    else if (cmd == "-scriptfile") {
      if (i + 1 == arg) {
        // no 
        cerr << "no scriptfile field" << endl;
      }
      else {
        scriptFile = argv[i + 1];
        i++;
      }

    } 
    else if (cmd == "-startlevel") {
      if (i + 1 == arg) {
        // no start
        istringstream iss {arg[i + 1]};
        if (!(iss >> startLevel) && 
          (startLevel > MAX_LEVEL || startLevel < MIN_LEVEL )) {
          cerr << "wrong level" << endl;
          return 1;
        }

      }
      i++;

    }

  }


  catch (ios::failure &) {}  // Any I/O failure quits
}
