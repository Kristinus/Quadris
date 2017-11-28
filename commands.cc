#include "commands.h"

void Command::SequenceCommand execute() {

	string s;
    string file;
    *in>>file;
    ifstream inputFile(file);
    while(inputFile >> s) {
    

    }

}

