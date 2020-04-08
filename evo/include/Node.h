#pragma once

#include <cstdint>
#include <limits>

using NodeIndex = std::uint8_t;
inline constexpr NodeIndex MAX_NODES = std::numeric_limits<NodeIndex>::max();
inline constexpr NodeIndex BIAS_INDEX = 0;

enum class NodeType { INPUT, OUTPUT, HIDDEN };
