CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD -g
EXEC = quadris
OBJECTS = main.o textDisplay.o graphicsDisplay.o window.o block.o interpreter.o blocks.o command.o commands.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
