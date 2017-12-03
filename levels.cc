#include "levels.h"
#include <algorithm>
#include "blocks.h"
#include "grid.h"

Level0::Level0(Grid * grid, int seed, std::string file): Level(grid, seed, file, false) {
    seq.open(sourceFile);
}

Block *Level0::createBlock() {
    char b;
    seq >> b;
    Block *block = getBlock(b);
    if(block) return block;
    //Loops through file again
    seq.close();
    seq.open(sourceFile);
        return createBlock();
}

Level0::~Level0() {
    seq.close();
}
Level* Level0::levelUp() {
    return new Level1(grid, seed, sourceFile);
}

Level* Level0::levelDown() {
    return this;
}

int Level0::getLevel() {
    return 0;
}

void Level0::restart() {
    seq.close();
    seq.open(sourceFile);
    srand(seed);
}


//***************************************************************************************//

Level1::Level1(Grid * grid, int seed, std::string file): Level(grid, seed, file, false) {
    setDefaultSelector(2,2,2,2,1,2,1);
}

Block *Level1::createBlock() {
    return selector[std::rand()%12](1,false);
}

Level* Level1::levelUp() {
    return new Level2(grid, seed, sourceFile);
}

Level* Level1::levelDown() {
    return new Level0(grid, seed, sourceFile);
}

int Level1::getLevel() {
    return 1;
}

//***************************************************************************************//

Level2::Level2(Grid * grid, int seed, std::string file): Level(grid, seed, file, false) {
    setDefaultSelector(1,1,1,1,1,1,1);
}

Block *Level2::createBlock() {
    return selector[std::rand()%7](2,false);
}
Level* Level2::levelUp() {
    return new Level3(grid, seed, sourceFile);
}

Level* Level2::levelDown() {
    return new Level1(grid, seed, sourceFile);
}

int Level2::getLevel() {
    return 2;
}

//***************************************************************************************//

Level3::Level3(Grid * grid, int seed, std::string file): Level(grid, seed, file, true) {
    setDefaultSelector(1,1,1,1,2,1,2);
}

Block *Level3::createBlock() {
    if(random)
        return selector[std::rand()%9](3,true);
    return generateFromFile(true);
}
Level* Level3::levelUp() {
    return new Level4(grid, seed, sourceFile);
}

Level* Level3::levelDown() {
    return new Level2(grid, seed, sourceFile);
}

int Level3::getLevel() {
    return 3;
}

//***************************************************************************************//

Level4::Level4(Grid * grid, int seed, std::string file): Level(grid, seed, file, true) {
    setDefaultSelector(1,1,1,1,2,1,2);
}

Block *Level4::createBlock() {
    counter++;
    if(counter==5) {
        counter = 0;
        grid->dropBlock(new DotBlock(getLevel(), heavy), 5);
    }
    if(random)
        return selector[std::rand()%9](4,true);
    return generateFromFile(true);
}

Level* Level4::levelUp() {
    return this;
}

Level* Level4::levelDown() {
    return new Level3(grid, seed, sourceFile);
}

int Level4::getLevel() {
    return 4;
}

void Level4::restart() {
    counter = 0;
    srand(seed);
}
