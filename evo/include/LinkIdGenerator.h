#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

class LinkIdGenerator
{
public:
    int get(int from, int to);
    int test(int from, int to) const;
private:
    std::unordered_map<int, std::unordered_map<int, int>> _links;
    int _count = 0;
};
