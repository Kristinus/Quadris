#ifndef __INVALID_INPUT_EXCEPTION_
#define __INVALID_INPUT_EXCEPTION_
#include <string>

struct InvalidInputException {
	std::string message;
	InvalidInputException(std::string message);
};

#endif
