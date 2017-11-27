#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <map>

enum class BlockType { I, J, K, L, O, S, T, Z }
enum class StateType { NONE, STATIC, MOVING}

struct Constants {
    const std::map<BlockType, char> BLOCK_CHARS {
        {BlockType::I, 'I'},
        {BlockType::J, 'J'},
        {BlockType::K, 'K'},
        {BlockType::L, 'L'},
        {BlockType::O, 'O'},
        {BlockType::S, 'S'},
        {BlockType::T, 'T'},
        {BlockType::Z, 'Z'},
    }
}

