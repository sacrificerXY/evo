#include "LinkIdGenerator.h"

#include <doctest/doctest.h>


int LinkIdGenerator::get(int from, int to)
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

int LinkIdGenerator::test(int from, int to) const
{
    REQUIRE(from >= 0);
    REQUIRE(to >= 0);
    
    if (!_links.contains(from)) {
        return _count;
    }
    else if (!_links.at(from).contains(to)) {
        return _count;
    }
    else {
        return _links.at(from).at(to);
    }
}

TEST_CASE("LinkIdGenerator")
{
    // checking out of order
    auto gen = LinkIdGenerator{};
    const auto get = [&gen] (int from, int to) {
        return gen.get(from, to);
    };
    const auto test = [&gen] (int from, int to) {
        return gen.test(from, to);
    };
    auto a = get(0, 0);
    auto b = get(1, 2);
    REQUIRE(get(0, 0) == a);
    auto c = get(3, 4);
    REQUIRE(get(3, 4) == c);
    auto d = get(5, 6);
    REQUIRE(get(5, 6) == d);
    REQUIRE(get(1, 2) == b);
    
    REQUIRE(get(5, 6) == test(5, 6));
    REQUIRE(get(1, 2) == test(1, 2));
    REQUIRE(get(0, 0) == test(0, 0));
    REQUIRE(get(3, 4) == test(3, 4));
    
    REQUIRE(a == 0);
    REQUIRE(b == 1);
    REQUIRE(c == 2);
    REQUIRE(d == 3);
}
