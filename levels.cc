#include "levels.h"
#include "constants.h"
#include <algorithm>
#include "blocks.h"

Level0::Level0() {
    seq.open(sourceFile);
}

Block *Level0::createBlock() {
    char b;
    seq >> b;
    if (b=='I')
        return new IBlock();
    else if (b=='J')
        return new JBlock();
    else if (b=='L')
        return new LBlock();
    else if (b=='O')
        return new OBlock();
    else if (b=='S')
        return new SBlock();
    else if (b=='T')
        return new TBlock();
    else if (b=='Z')
        return new ZBlock();
    //Invalid file.txt
}

Level0::~Level0() {
    seq.close();
}

//***************************************************************************************//

Level1::Level1():
    selector{std::vector<Block *>{new IBlock(), new IBlock(), new JBlock(), new JBlock(), new LBlock(), new LBlock(), new OBlock(), new OBlock(), new SBlock(), new TBlock(), new TBlock(), new ZBlock()}} {
}

Block *Level1::createBlock() {
    return selector[std::rand()%13];
}

//***************************************************************************************//

Level2::Level2():
selector{std::vector<Block *>{new IBlock(), new JBlock(), new LBlock(), new OBlock(), new SBlock(), new TBlock(), new ZBlock()}} {
}

Block *Level2::createBlock() {
    return selector[std::rand()%8];
}

//***************************************************************************************//

Level3::Level3():
selector{std::vector<Block *>{new IBlock(), new JBlock(), new LBlock(), new OBlock(), new SBlock(), new TBlock(), new ZBlock(), new SBlock(), new ZBlock()}} {
}

Block *Level3::createBlock() {
    return selector[std::rand()%10];
}

//***************************************************************************************//

Level4::Level4():
selector{std::vector<Block *>{new IBlock(), new JBlock(), new LBlock(), new OBlock(), new SBlock(), new TBlock(), new ZBlock(), new SBlock(), new ZBlock()}} {
}

Block *Level4::createBlock() {
    return selector[std::rand()%10];
}

