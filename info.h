#ifndef __INFO_H__
#define __INFO_H__
#include <cstddef>
#include "state.h"

enum class StateType { NONE, MOVING, STATIC };
enum class BlockType { I, J, L, O, S, T, Z };

struct Info {
  size_t row, col;
  StateType state;
  BlockType block;
};

#endif
