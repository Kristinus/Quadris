#include "level.h"
#include "blocks.h"

// Block *Level::createIBlock() {
//     return new IBlock();
// }

void Level::setDefaultSelector(int i, int j, int l, int o, int s, int t, int z) {
    for(;i>0;--i)
        selector.emplace_back([](int a, bool b)->Block *{return new IBlock(a, b);});
    for(;j>0;--j)
        selector.emplace_back([](int a, bool b)->Block *{return new JBlock(a, b);});
    for(;l>0;--l)
        selector.emplace_back([](int a, bool b)->Block *{return new LBlock(a, b);});
    for(;o>0;--o)
        selector.emplace_back([](int a, bool b)->Block *{return new OBlock(a, b);});
    for(;s>0;--s)
        selector.emplace_back([](int a, bool b)->Block *{return new SBlock(a, b);});
    for(;t>0;--t)
        selector.emplace_back([](int a, bool b)->Block *{return new TBlock(a, b);});
    for(;z>0;--z)
        selector.emplace_back([](int a, bool b)->Block *{return new ZBlock(a, b);});
}

void Level::setSeed(int seed) {
    this->seed = seed;
}

Level::~Level() {}
