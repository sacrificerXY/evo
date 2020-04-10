#include "GenomeLinkIdGenerator.h"

#include <doctest/doctest.h>

int GenomeLinkIdGenerator::operator()(int from, int to) const
{
    REQUIRE(from >= 0);
    REQUIRE(to >= 0);
    
    if (!_links.contains(from)) {
        _links[from][to] = _count++;
    }
    else if (!_links[from].contains(to)) {
        _links[from][to] = _count++;
    }
    
    return _links[from][to];
}

TEST_CASE("GenomeLinkIdGenerator ")
{
    auto gen = GenomeLinkIdGenerator{};
    // checking out of order
    auto a = gen(0, 0);
    auto b = gen(1, 2);
    REQUIRE(gen(0, 0) == a);
    auto c = gen(3, 4);
    REQUIRE(gen(3, 4) == c);
    auto d = gen(5, 6);
    REQUIRE(gen(5, 6) == d);
    REQUIRE(gen(1, 2) == b);
    
    REQUIRE(a == 0);
    REQUIRE(b == 1);
    REQUIRE(c == 2);
    REQUIRE(d == 3);
}

namespace _internal
{
    bool operator==(const _link& l, const _link& r)
    {
        return l.from == r.from && l.to == r.to;
    }
    
}