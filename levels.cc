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
Level* Level0::levelUp() {
    return new Level1();
}

Level* Level0::levelDown() {
    return this;
}

int Level0::getLevel() {
    return 0;
}


//***************************************************************************************//

Level1::Level1() {
    setDefaultSelector();
    selector.emplace_back(new IBlock());
    selector.emplace_back(new JBlock());
    selector.emplace_back(new LBlock());
    selector.emplace_back(new OBlock());
    selector.emplace_back(new TBlock());
}

Block *Level1::createBlock() {
    return selector[std::rand()%12];
}

Level* Level1::levelUp() {
    return new Level2();
}

Level* Level1::levelDown() {
    return new Level0();
}

int Level1::getLevel() {
    return 1;
}

//***************************************************************************************//

Level2::Level2() {
    setDefaultSelector();
}

Block *Level2::createBlock() {
    return selector[std::rand()%7];
}
Level* Level2::levelUp() {
    return new Level3();
}

Level* Level2::levelDown() {
    return new Level1();
}

int Level2::getLevel() {
    return 2;
}

//***************************************************************************************//

Level3::Level3() {
    setDefaultSelector();
    selector.emplace_back(new SBlock());
    selector.emplace_back(new ZBlock());
}

Block *Level3::createBlock() {
    return selector[std::rand()%9];
}
Level* Level3::levelUp() {
    return new Level4();
}

Level* Level3::levelDown() {
    return new Level2();
}

int Level3::getLevel() {
    return 3;
}

//***************************************************************************************//

Level4::Level4() {
    setDefaultSelector();
    selector.emplace_back(new SBlock());
    selector.emplace_back(new ZBlock());
}

Block *Level4::createBlock() {
    return selector[std::rand()%9];
}

Level* Level4::levelUp() {
    return this;
}

Level* Level4::levelDown() {
    return new Level3();
}

int Level4::getLevel() {
    return 4;
}

