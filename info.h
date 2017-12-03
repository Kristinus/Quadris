#ifndef __INFO_H__
#define __INFO_H__
#include <cstddef>


enum class StateType { NONE, MOVING, STATIC, NEXT };
enum class BlockType { NONE, I, J, L, O, S, T, Z, HINT };

struct Info {
  size_t row, col;
  StateType state;
  BlockType block;
};

#endif
