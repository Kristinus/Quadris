#include "levels.h"
#include "constants.h"
#include <algorithm>

Level0::Level0() {
    seq.open(sourceFile);
}

Block Level0::createBlock() {
    char b;
    seq >> b;
    if (std::find(BLOCKS.begin(), BLOCKS.end(), b) !=BLOCKS.end())
        return Block(b);
    //Invalid file.txt
}

Level0::~Level0() {
    seq.close();
}

//***************************************************************************************//

Level1::Level1():
    selector{std::vector<Block>{Block('I'), Block('I'), Block('J'), Block('J'), Block('L'), Block('L'), Block('O'), Block('O'), Block('S'), Block('T'), Block('T'), Block('Z')}} {
}

Block Level1::createBlock() {
    return selector[std::rand()%13];
}

//***************************************************************************************//

Level2::Level2():
selector{std::vector<Block>{Block('I'), Block('J'), Block('L'), Block('O'), Block('S'), Block('T'), Block('Z')}} {
}

Block Level2::createBlock() {
    return selector[std::rand()%8];
}

//***************************************************************************************//

Level3::Level3():
selector{std::vector<Block>{Block('I'), Block('J'), Block('L'), Block('O'), Block('S'), Block('T'), Block('Z'), Block('S'), Block('Z')}} {
}

Block Level3::createBlock() {
    return selector[std::rand()%10];
}

//***************************************************************************************//

Level4::Level4():
selector{std::vector<Block>{Block('I'), Block('J'), Block('L'), Block('O'), Block('S'), Block('T'), Block('Z'), Block('S'), Block('Z')}} {
}

Block Level4::createBlock() {
    return selector[std::rand()%10];
}

