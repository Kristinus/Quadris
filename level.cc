#include "level.h"
#include "blocks.h"

// Block *Level::createIBlock() {
//     return new IBlock();
// }

Level::Level(Grid *grid, int seed, std::string file, bool heavy): grid{grid}, seed{seed},sourceFile{file}, heavy{heavy} {
    srand(seed);
}

Block *Level::generateFromFile(bool heavy) {
    char b;
    seq >> b;
    Block *block = getBlock(b);
    if(block) return block;
    //Loops through file again
    seq.close();
    seq.open(randFile);
        return generateFromFile(heavy);
}

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

Block * Level::getBlock(char b) {
    if (b=='I')
        return new IBlock(getLevel(), heavy);
    else if (b=='J')
        return new JBlock(getLevel(), heavy);
    else if (b=='L')
        return new LBlock(getLevel(), heavy);
    else if (b=='O')
        return new OBlock(getLevel(), heavy);
    else if (b=='S')
        return new SBlock(getLevel(), heavy);
    else if (b=='T')
        return new TBlock(getLevel(), heavy);
    else if (b=='Z')
        return new ZBlock(getLevel(), heavy);
    return nullptr;
}

Block * Level::getBlock(BlockType type) {
    if (type==BlockType::I)
        return new IBlock(getLevel(), heavy);
    else if (type==BlockType::J)
        return new JBlock(getLevel(), heavy);
    else if (type==BlockType::L)
        return new LBlock(getLevel(), heavy);
    else if (type==BlockType::O)
        return new OBlock(getLevel(), heavy);
    else if (type==BlockType::S)
        return new SBlock(getLevel(), heavy);
    else if (type==BlockType::T)
        return new TBlock(getLevel(), heavy);
    else if (type==BlockType::Z)
        return new ZBlock(getLevel(), heavy);
    return nullptr;
}

void Level::setSeed(int seed) {
    this->seed = seed;
    srand(seed);
}

void Level::setRandom(bool flag) {
    random = flag;
    if(!random) seq.open(randFile);
    else seq.close();
}

void Level::setFile(std::string file) {
    randFile = file;
    setRandom(true);
}

bool Level::isHeavy() {
    return heavy;
}

Level::~Level() {}
