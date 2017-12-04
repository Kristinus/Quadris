#include "level.h"
#include "blocks.h"

Level::Level(Grid *grid, int seed, std::string file, bool heavy): grid{grid}, seed{seed},sourceFile{file}, heavy{heavy} {
    srand(seed);
}


// Generates block from sequence file
Block *Level::generateFromFile(bool heavy) {
    char b;
    seq >> b;
    Block *block = getBlock(b, getLevel(), heavy);
    if(block) return block;

    // Loops through file again
    seq.close();
    seq.open(randFile);

    return generateFromFile(heavy);
}


// Sets the block selector
void Level::setSelector(int i, int j, int l, int o, int s, int t, int z) {
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


// Gets a new block given the block letter
Block * Level::getBlock(char b, int level, bool heavy) {
    if (b=='I')
        return new IBlock(level, heavy);
    else if (b=='J')
        return new JBlock(level, heavy);
    else if (b=='L')
        return new LBlock(level, heavy);
    else if (b=='O')
        return new OBlock(level, heavy);
    else if (b=='S')
        return new SBlock(level, heavy);
    else if (b=='T')
        return new TBlock(level, heavy);
    else if (b=='Z')
        return new ZBlock(level, heavy);
    return nullptr;
}


// Gets a new block given the BlockType
Block * Level::getBlock(BlockType type, int level, bool heavy) {
    if (type==BlockType::I)
        return new IBlock(level, heavy);
    else if (type==BlockType::J)
        return new JBlock(level, heavy);
    else if (type==BlockType::L)
        return new LBlock(level, heavy);
    else if (type==BlockType::O)
        return new OBlock(level, heavy);
    else if (type==BlockType::S)
        return new SBlock(level, heavy);
    else if (type==BlockType::T)
        return new TBlock(level, heavy);
    else if (type==BlockType::Z)
        return new ZBlock(level, heavy);
    return nullptr;
}


void Level::setSeed(int seed) {
    this->seed = seed;
    srand(seed);
}


// Sets the randomness of the level
void Level::setRandom(bool flag) {
    random = flag;
    if(!random) seq.open(randFile);
    else seq.close();
}


// Sets the sequence file for norandom
void Level::setFile(std::string file) {
    randFile = file;
    setRandom(true);
}


bool Level::isHeavy() {
    return heavy;
}


void Level::restart() {
    srand(seed);
}


void Level::setCounter(int i) {}


Level::~Level() {}

