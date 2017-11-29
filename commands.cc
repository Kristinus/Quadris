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


void LCommand::execute(int m) {
}


void ICommand::execute(int m) {

}



void JCommand::execute(int m) {

}

void OCommand::execute(int m) {

}

void SCommand::execute(int m) {

}

void ZCommand::execute(int m) {

}

void TCommand::execute(int m) {

}

