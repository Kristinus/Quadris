
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <map>
#include <vector>
namespace constants {
	const int GRID_HEIGHT = 18;
	const int GRID_WIDTH = 11;
	const int MIN_LEVEL = 0;
	const int MAX_LEVEL = 4;
	const string DEFAULT_SCRIPT_FILE = "sequence.txt";
	const std::vector<char> BLOCKS = {
		'I','J','L','O','S','T','Z'
	};
}

#endif
