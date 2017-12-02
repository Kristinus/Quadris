#include "levels.h"
#include "constants.h"
#include <algorithm>
#include "blocks.h"

Level0::Level0() {}

Level0::Level0(int seed): Level(seed) {
    seq.open(sourceFile);
}

Block *Level0::createBlock() {
    char b;
    seq >> b;
    if (b=='I')
        return new IBlock(0);
    else if (b=='J')
        return new JBlock(0);
    else if (b=='L')
        return new LBlock(0);
    else if (b=='O')
        return new OBlock(0);
    else if (b=='S')
        return new SBlock(0);
    else if (b=='T')
        return new TBlock(0);
    else if (b=='Z')
        return new ZBlock(0);
    //Loops through file again
    seq.close();
    seq.open(sourceFile);
        return createBlock();
}

Level0::~Level0() {
    seq.close();
}
Level* Level0::levelUp() {
    return new Level1(seed);
}

Level* Level0::levelDown() {
    return this;
}

int Level0::getLevel() {
    return 0;
}


//***************************************************************************************//

Level1::Level1() {
    setDefaultSelector(2,2,2,2,1,2,1);
}

Level1::Level1(int seed): Level(seed) {
    setDefaultSelector(2,2,2,2,1,2,1);
}

Block *Level1::createBlock() {
    return selector[std::rand()%12](1,false);
}

Level* Level1::levelUp() {
    return new Level2(seed);
}

Level* Level1::levelDown() {
    return new Level0(seed);
}

int Level1::getLevel() {
    return 1;
}

//***************************************************************************************//

Level2::Level2() {
    setDefaultSelector(1,1,1,1,1,1,1);
}

Level2::Level2(int seed): Level(seed) {
    setDefaultSelector(1,1,1,1,1,1,1);
}

Block *Level2::createBlock() {
    return selector[std::rand()%7](2,false);
}
Level* Level2::levelUp() {
    return new Level3(seed);
}

Level* Level2::levelDown() {
    return new Level1(seed);
}

int Level2::getLevel() {
    return 2;
}

//***************************************************************************************//

Level3::Level3() {
    setDefaultSelector(1,1,1,1,2,1,2);
}

Level3::Level3(int seed): Level(seed) {
    setDefaultSelector(1,1,1,1,2,1,2);
}

Block *Level3::createBlock() {
    return selector[std::rand()%9](3,true);
}
Level* Level3::levelUp() {
    return new Level4(seed);
}

Level* Level3::levelDown() {
    return new Level2(seed);
}

int Level3::getLevel() {
    return 3;
}

//***************************************************************************************//

Level4::Level4() {
    setDefaultSelector(1,1,1,1,2,1,2);
}

Level4::Level4(int seed): Level(seed) {
    setDefaultSelector(1,1,1,1,2,1,2);
}

Block *Level4::createBlock() {
    return selector[std::rand()%9](4, true);
}

Level* Level4::levelUp() {
    return this;
}

Level* Level4::levelDown() {
    return new Level3(seed);
}

int Level4::getLevel() {
    return 4;
}

