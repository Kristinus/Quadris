#include "level.h"
#include "blocks.h"

Level::Level(Grid *grid, int seed, std::string file, bool heavy): grid{grid}, seed{seed},sourceFile{file}, heavy{heavy} {
    srand(seed);
}


// Generates block from sequence file
std::unique_ptr<Block> Level::generateFromFile(bool heavy) {
    char b;
    if(seq >> b) {
        return std::move(getBlock(b, getLevel(), heavy));
    }

    // Loops through file again
    seq.close();
    seq.open(randFile);

    return generateFromFile(heavy);
}


// Sets the block selector
void Level::setSelector(int i, int j, int l, int o, int s, int t, int z) {
    for(;i>0;--i)
        selector.emplace_back([](int a, bool b)->std::unique_ptr<Block>{return std::make_unique<IBlock>(a, b);});
    for(;j>0;--j)
        selector.emplace_back([](int a, bool b)->std::unique_ptr<Block>{return std::make_unique<JBlock>(a, b);});
    for(;l>0;--l)
        selector.emplace_back([](int a, bool b)->std::unique_ptr<Block>{return std::make_unique<LBlock>(a, b);});
    for(;o>0;--o)
        selector.emplace_back([](int a, bool b)->std::unique_ptr<Block>{return std::make_unique<OBlock>(a, b);});
    for(;s>0;--s)
        selector.emplace_back([](int a, bool b)->std::unique_ptr<Block>{return std::make_unique<SBlock>(a, b);});
    for(;t>0;--t)
        selector.emplace_back([](int a, bool b)->std::unique_ptr<Block>{return std::make_unique<TBlock>(a, b);});
    for(;z>0;--z)
        selector.emplace_back([](int a, bool b)->std::unique_ptr<Block>{return std::make_unique<ZBlock>(a, b);});
}


// Gets a new block given the block letter
std::unique_ptr<Block> Level::getBlock(char b, int level, bool heavy) {
    if (b=='I')
        return std::make_unique<IBlock>(level, heavy);
    else if (b=='J')
        return std::make_unique<JBlock>(level, heavy);
    else if (b=='L')
        return std::make_unique<LBlock>(level, heavy);
    else if (b=='O')
        return std::make_unique<OBlock>(level, heavy);
    else if (b=='S')
        return std::make_unique<SBlock>(level, heavy);
    else if (b=='T')
        return std::make_unique<TBlock>(level, heavy);
    return std::make_unique<ZBlock>(level, heavy);
}


// Gets a new block given the BlockType
std::unique_ptr<Block> Level::getBlock(BlockType type, int level, bool heavy) {
    if (type==BlockType::I)
        return std::make_unique<IBlock>(level, heavy);
    else if (type==BlockType::J)
        return std::make_unique<JBlock>(level, heavy);
    else if (type==BlockType::L)
        return std::make_unique<LBlock>(level, heavy);
    else if (type==BlockType::O)
        return std::make_unique<OBlock>(level, heavy);
    else if (type==BlockType::S)
        return std::make_unique<SBlock>(level, heavy);
    else if (type==BlockType::T)
        return std::make_unique<TBlock>(level, heavy);
    return std::make_unique<ZBlock>(level, heavy);
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

