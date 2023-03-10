#ifndef __INFO_H__
#define __INFO_H__

#include <cstddef>

enum class StateType { NONE, MOVING, STATIC, NEXT, HOLD };
enum class BlockType { NONE, I, J, L, O, S, T, Z, HINT, DOT };

struct Info {
  size_t row, col;
  StateType state;
  BlockType block;
};

#endif
