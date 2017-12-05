#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <map>
#include <vector>
#include <string>

namespace constants {
	const int GRID_HEIGHT = 18;
	const int GRID_WIDTH = 11;
	const int MIN_LEVEL = 0;
	const int MAX_LEVEL = 4;
	const int MAX_ROW = 14;
	const int MIN_COL = 0;
	const int MAX_COL = 11;
	const int MIN_ROW = 0;
	
	const std::string DEFAULT_SCRIPT_FILE = "sequence.txt";
	const std::vector<char> BLOCKS = {
		'I','J','L','O','S','T','Z'
	};
	const std::string NO_INPUT = "Invalid Input: Please provide a command.";
}

#endif
