#include "commands.h"
#include "grid.h"


void LeftCommand::execute(int m) {
    grid->left(m);
}

void RightCommand::execute(int m) {
    grid->right(m);
}

void DownCommand::execute(int m) {
    grid->down(m);
}

void ClockwiseCommand::execute(int m) {
    grid->rotateCW(m);
}

void CounterClockwiseCommand::execute(int m) {
    grid->rotateCCW(m);
}

void DropCommand::execute(int m) {
    grid->drop(m);
}


void LCommand::execute(int m=1) {
}


void ICommand::execute(int m=1) {

}



void JCommand::execute(int m=1) {

}

void OCommand::execute(int m=1) {

}

void SCommand::execute(int m=1) {

}

void ZCommand::execute(int m=1) {

}

void TCommand::execute(int m=1) {

}

