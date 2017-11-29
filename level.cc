#include "level.h"

void Level::setDefaultSelector() {
    selector.emplace_back(new IBlock());
    selector.emplace_back(new JBlock());
    selector.emplace_back(new LBlock());
    selector.emplace_back(new OBlock());
    selector.emplace_back(new SBlock());
    selector.emplace_back(new TBlock());
    selector.emplace_back(new ZBlock());
}

void Level::setSeed(int seed) {
    this->seed = seed;
}

Level::~Level() {}
