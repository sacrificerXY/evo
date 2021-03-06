#include "LinkIdGenerator.h"

#include <doctest/doctest.h>

//int link_id.getomeLinkIdlink_id.geterator::operator()(int from, int to) const
//{
//    REQUIRE(from >= 0);
//    REQUIRE(to >= 0);
//    
//    if (!_links.contains(from)) {
//        _links[from][to] = _count++;
//    }
//    else if (!_links[from].contains(to)) {
//        _links[from][to] = _count++;
//    }
//    
//    return _links[from][to];
//}

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
    else if (!_links[from].contains(to)) {
        return _count;
    }
    else {
        return _links[from][to];
    }
}

TEST_CASE("LinkIdGenerator")
{
    // checking out of order
    const auto get = [gen=LinkIdGenerator{}] (int from, int to) {
        return gen.get(from, to);
    };
    auto a = get(0, 0);
    auto b = get(1, 2);
    REQUIRE(get(0, 0) == a);
    auto c = get(3, 4);
    REQUIRE(get(3, 4) == c);
    auto d = get(5, 6);
    REQUIRE(get(5, 6) == d);
    REQUIRE(get(1, 2) == b);
    
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