CXX = g++
CXXFLAGS = -fPIE -std=c++14 -Wall -pthread -Werror=vla -MMD -g -O0 
EXEC = quadris
OBJECTS = main.o level.o levels.o textDisplay.o invalidinputexception.o graphicsDisplay.o window.o interpreter.o commands.o command.o block.o blocks.o grid.o cell.o score.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
