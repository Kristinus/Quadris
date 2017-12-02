#include "levels.h"
#include "constants.h"
#include <algorithm>
#include "blocks.h"

Level0::Level0(int seed, std::string file): Level(seed, file, false) {
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
    return new Level1(seed, sourceFile);
}

Level* Level0::levelDown() {
    return this;
}

int Level0::getLevel() {
    return 0;
}


//***************************************************************************************//

Level1::Level1(int seed, std::string file): Level(seed, file, false) {
    setDefaultSelector(2,2,2,2,1,2,1);
}

Block *Level1::createBlock() {
    return selector[std::rand()%12](1,false);
}

Level* Level1::levelUp() {
    return new Level2(seed, sourceFile);
}

Level* Level1::levelDown() {
    return new Level0(seed, sourceFile);
}

int Level1::getLevel() {
    return 1;
}

//***************************************************************************************//

Level2::Level2(int seed, std::string file): Level(seed, file, false) {
    setDefaultSelector(1,1,1,1,1,1,1);
}

Block *Level2::createBlock() {
    return selector[std::rand()%7](2,false);
}
Level* Level2::levelUp() {
    return new Level3(seed, sourceFile);
}

Level* Level2::levelDown() {
    return new Level1(seed, sourceFile);
}

int Level2::getLevel() {
    return 2;
}

//***************************************************************************************//

Level3::Level3(int seed, std::string file): Level(seed, file, true) {
    setDefaultSelector(1,1,1,1,2,1,2);
}

Block *Level3::createBlock() {
    if(random)
        return selector[std::rand()%9](3,true);
    return generateFromFile(true);
}
Level* Level3::levelUp() {
    return new Level4(seed, sourceFile);
}

Level* Level3::levelDown() {
    return new Level2(seed, sourceFile);
}

int Level3::getLevel() {
    return 3;
}

//***************************************************************************************//

Level4::Level4(int seed, std::string file): Level(seed, file, true) {
    setDefaultSelector(1,1,1,1,2,1,2);
}

Block *Level4::createBlock() {
    if(random)
        return selector[std::rand()%9](4,true);
    return generateFromFile(true);
}

Level* Level4::levelUp() {
    return this;
}

Level* Level4::levelDown() {
    return new Level3(seed, sourceFile);
}

int Level4::getLevel() {
    return 4;
}

