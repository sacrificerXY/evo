#pragma once

#include <cstdint>
#include <functional>

#include "Node.h"
using LinkId = std::uint16_t;

struct Link {
    NodeIndex from;
    NodeIndex to;
};

bool operator==(Link l, Link r);
bool operator!=(Link l, Link r);

namespace std
{
template <> struct hash<Link> {
    auto operator()(const Link& l) const
    {
        return (std::hash<decltype(l.from)>{}(l.from) << 16) | std::hash<decltype(l.to)>{}(l.to);
    }
};
}
