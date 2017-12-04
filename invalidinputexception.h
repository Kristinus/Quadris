#ifndef __INVALID_INPUT_EXCEPTION__
#define __INVALID_INPUT_EXCEPTION__

#include <string>

struct InvalidInputException {
	std::string message;
	InvalidInputException(std::string message);
};

#endif
