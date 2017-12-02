#include "commands.h"
#include "grid.h"

LeftCommand::LeftCommand(Grid *g): Command(g) {}

void LeftCommand::execute(int m) {
    grid->left(m);
}

/******************************************************************************/

RightCommand::RightCommand(Grid *g): Command(g) {}

void RightCommand::execute(int m) {
    grid->right(m);
}

/******************************************************************************/

DownCommand::DownCommand(Grid *g): Command(g) {}

void DownCommand::execute(int m) {
    grid->down(m);
}

/******************************************************************************/

ClockwiseCommand::ClockwiseCommand(Grid *g): Command(g) {}

void ClockwiseCommand::execute(int m) {
    grid->rotateCW(m);
}

/******************************************************************************/

CounterClockwiseCommand::CounterClockwiseCommand(Grid *g): Command(g) {}

void CounterClockwiseCommand::execute(int m) {
    grid->rotateCCW(m);
}

/******************************************************************************/

DropCommand::DropCommand(Grid *g): Command(g) {}

void DropCommand::execute(int m) {
    grid->drop(m);
}

/******************************************************************************/

LevelUpCommand::LevelUpCommand(Grid *g): Command(g) {}

void LevelUpCommand::execute(int m) {
    grid->levelUp(m);
}

/******************************************************************************/

LevelDownCommand::LevelDownCommand(Grid *g): Command(g) {}

void LevelDownCommand::execute(int m) {
    grid->levelDown(m);
}

/******************************************************************************/

NoRandomCommand::NoRandomCommand(Grid *g): Command(g) {}

void NoRandomCommand::execute(int m) {
    grid->random(false);
}

/******************************************************************************/

RandomCommand::RandomCommand(Grid *g): Command(g) {}

void RandomCommand::execute(int m) {
    grid->random(true);
}

/******************************************************************************/

SequenceCommand::SequenceCommand(Grid *g): Command(g) {}

void SequenceCommand::execute(int m) {
}

/******************************************************************************/

RestartCommand::RestartCommand(Grid *g): Command(g) {}

void RestartCommand::execute(int m) {
    grid->restart();
}

/******************************************************************************/

HintCommand::HintCommand(Grid *g): Command(g) {}

void HintCommand::execute(int m) {
    grid->hint();
}


// void LCommand::execute(int m) {
// }


// void ICommand::execute(int m) {

// }



// void JCommand::execute(int m) {

// }

// void OCommand::execute(int m) {

// }

// void SCommand::execute(int m) {

// }

// void ZCommand::execute(int m) {

// }

// void TCommand::execute(int m) {

// }

