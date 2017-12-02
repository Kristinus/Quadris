#include "commands.h"
#include "grid.h"
#include "interpreter.h"

LeftCommand::LeftCommand(Grid *g): Command(g) {}

void LeftCommand::execute(int m, std::string file) {
    grid->left(m);
}

/******************************************************************************/

RightCommand::RightCommand(Grid *g): Command(g) {}

void RightCommand::execute(int m, std::string file) {
    grid->right(m);
}

/******************************************************************************/

DownCommand::DownCommand(Grid *g): Command(g) {}

void DownCommand::execute(int m, std::string file) {
    grid->down(m);
}

/******************************************************************************/

ClockwiseCommand::ClockwiseCommand(Grid *g): Command(g) {}

void ClockwiseCommand::execute(int m, std::string file) {
    grid->rotateCW(m);
}

/******************************************************************************/

CounterClockwiseCommand::CounterClockwiseCommand(Grid *g): Command(g) {}

void CounterClockwiseCommand::execute(int m, std::string file) {
    grid->rotateCCW(m);
}

/******************************************************************************/

DropCommand::DropCommand(Grid *g): Command(g) {}

void DropCommand::execute(int m, std::string file) {
    grid->drop(m);
}

/******************************************************************************/

LevelUpCommand::LevelUpCommand(Grid *g): Command(g) {}

void LevelUpCommand::execute(int m, std::string file) {
    grid->levelUp(m);
}

/******************************************************************************/

LevelDownCommand::LevelDownCommand(Grid *g): Command(g) {}

void LevelDownCommand::execute(int m, std::string file) {
    grid->levelDown(m);
}

/******************************************************************************/

NoRandomCommand::NoRandomCommand(Grid *g): Command(g) {}

void NoRandomCommand::execute(int m, std::string file) {
    grid->random(false);
    grid->setRandomFile(file);
}

/******************************************************************************/

RandomCommand::RandomCommand(Grid *g): Command(g) {}

void RandomCommand::execute(int m, std::string file) {
    grid->random(true);
}

/******************************************************************************/

SequenceCommand::SequenceCommand(Grid *g, Interpreter *i): Command(g), i{i} {}

void SequenceCommand::execute(int m, std::string file) {
    seq.open(file);
    i->run(seq);
    seq.close();
}

/******************************************************************************/

RestartCommand::RestartCommand(Grid *g): Command(g) {}

void RestartCommand::execute(int m, std::string file) {
    grid->restart();
}

/******************************************************************************/

HintCommand::HintCommand(Grid *g): Command(g) {}

void HintCommand::execute(int m, std::string file) {
    grid->hint();
}


// void LCommand::execute(int m, std::string file) {
// }


// void ICommand::execute(int m, std::string file) {

// }



// void JCommand::execute(int m, std::string file) {

// }

// void OCommand::execute(int m, std::string file) {

// }

// void SCommand::execute(int m, std::string file) {

// }

// void ZCommand::execute(int m, std::string file) {

// }

// void TCommand::execute(int m, std::string file) {

// }

