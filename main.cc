#include <iostream>
#include <string>
#include <sstream>
#include "interpreter.h"
#include "constants.h"
#include "graphicsDisplay.h"
#include <ctime>
#include <thread>

using namespace std;

// NOTES:
// -text runs the program in text only mode (no graphics) defult is ns show both text and graphics
// -seed [number], sets the random number generator's seed to xxx
// -scriptfile xxx, use xxx instead of sequence as a source of blocks for level 0
// -startlevel [0-4], starts the game in level n... otherwise default is zero

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  bool textOnly = false;
  int seed = time(NULL);
  string scriptFile = constants::DEFAULT_SCRIPT_FILE;
  int startLevel = 0;

  bool keyInput = false;

  for (int i = 1; i < argc; ++i) {
    string cmd = argv[i];
    
    if (cmd == "-text") {
      textOnly = true;
    }
    else if (cmd == "-seed") {
      // Case for missing seed argument
      if (i + 1 == argc) {
        cerr << "Missing Argument: -seed [number] .";
        return 1;
      }
      else {
        // Check that seed is fed a number
        istringstream iss{argv[i + 1]};
        
        if (!(iss >> seed)) {
          cerr << "Invalid Input: Please provide a number for the seed" << endl;
          return 1;
        }

        i++;
      }
    }
    else if (cmd == "-scriptfile") {
      if (i + 1 == argc) {
        cerr << "Missing Argument: -scriptfile [filename]" << endl;
        return 1;
      }
      else {
        scriptFile = argv[i + 1];
        i++;
      }
    } 
    else if (cmd == "-startlevel") {
      if (i + 1 == argc) {
      // No start
      }
      else {
        istringstream iss {argv[i + 1]};

        // Check that the input is an integer and is one of the five levels
        if (!(iss >> startLevel) && 
          (startLevel > constants::MAX_LEVEL || startLevel < constants::MIN_LEVEL )) {
          cerr << "Invalid Input: Use -startlevel [integer between 0 - 4 ]" << endl;
          return 1;
        } 

        i++;
      }
    }
    else if (cmd == "-keys") {
        keyInput = true;
    }
  }

  // GraphicsDisplay *gd = nullptr;
  std::shared_ptr<GraphicsDisplay> gd;
  if(!textOnly || keyInput) {
    // gd = new GraphicsDisplay();
    gd = std::make_shared<GraphicsDisplay>();
  }

  // GraphicsDisplay *ob = nullptr;
  Interpreter in = Interpreter(seed, gd, scriptFile, startLevel);
  try {
    if (!keyInput) in.run();
    else {
      cout << "select the window" << endl;
      cout << "CONTROLS:" << endl;
      cout << "UP_KEY: clockwise" << endl;
      cout << "RIGHT_KEY: right" << endl;
      cout << "DOWN_KEY: down" << endl;
      cout << "LEFT_KEY: left" << endl;
      cout << "SPACE_KEY: drop" << endl;
      cout << "u_KEY: levelup" << endl;
      cout << "i_KEY: leveldown" << endl;
      cout << "q_KEY: quit" << endl;
      cout << "_KEY: leveldown" << endl;
      cout << "i_KEY: leveldown" << endl;
      cout << "r_KEY: restart" << endl;
      cout << "h_KEY: hint" << endl;
      
      gd->run(&in);
    }
  } catch (ios::failure &) {}  // Any I/O failure quits
}

