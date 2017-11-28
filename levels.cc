#include "levels.h"

Level0::Level0() {
    seq.open(sourceFile);
}

Block Level0::createBlock() {
    char b;
    seq >> b;
    if (b == 'I' || b =='J' || b == 'L' || b == 'O' || b == 'S' || b == 'T' || b == 'Z')
        return Block(b);
    //Invalid file.txt
}

Level0::~Level0() {
    seq.close();
}

//***************************************************************************************//

Level1::Level1():
    selector{std::vector<Block>{Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I')}} {
}

Block Level1::createBlock() {
    
}

//***************************************************************************************//

Level2::Level2():
selector{std::vector<Block>{Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I')}} {
}

Block Level2::createBlock() {
    
}

//***************************************************************************************//

Level3::Level3():
selector{std::vector<Block>{Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I')}} {
}

Block Level3::createBlock() {
    
}

//***************************************************************************************//

Level4::Level4():
selector{std::vector<Block>{Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I'), Block('I')}} {
}

Block Level4::createBlock() {
    
}

