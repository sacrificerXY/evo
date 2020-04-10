#pragma once

#include <functional>
#include <unordered_map>

namespace _internal
{
    struct _link { int from; int to; };
    
    bool operator==(const _link& l, const _link& r);
}

namespace std
{
    template <>
    struct hash<_internal::_link> {
        auto operator()(const _internal::_link& l) const
        {
            return (l.from + l.to) * (l.from + l.to + 1) / 2 + l.to;
        }
    };
}


class GenomeLinkIdGenerator
{
public:
    int operator()(int from, int to) const;
private:
    mutable std::unordered_map<int, std::unordered_map<int, int>> _links;
    mutable int _count = 0;
};