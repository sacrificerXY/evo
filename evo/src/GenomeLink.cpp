#include "GenomeLink.h"

#include <algorithm>
#include <doctest/doctest.h>

void
add_link(std::vector<GenomeLink>& links, const GenomeLink& link)
{
    REQUIRE_FALSE(has_link(links, link.id));
    const auto insertion_point = std::lower_bound(links.begin(), links.end(), link);
    links.insert(insertion_point, link);
}

void
disable_link(std::vector<GenomeLink>& links, int id)
{
    REQUIRE(has_link(links, id));
    const auto link = std::lower_bound(links.begin(), links.end(), id);
    REQUIRE(link->id == id);
    link->enabled = false;
}

bool
has_link(const std::vector<GenomeLink>& links, int id)
{
    auto it = std::lower_bound(links.begin(), links.end(), id);
    return it != links.end();
}

GenomeLink
get_link(const std::vector<GenomeLink>& links, int id)
{
    REQUIRE(has_link(links, id));
    const auto link = std::lower_bound(links.begin(), links.end(), id);
    REQUIRE(link->id == id);
    return *link;
}

bool operator==(const GenomeLink& l, const GenomeLink& r)
{
    return l.id == r.id
        && l.from == r.from
        && l.to == r.to
        && l.weight == r.weight
        && l.enabled == r.enabled;
}
bool operator<(const GenomeLink& l, const GenomeLink& r)
{
    return l.id < r.id;
}
bool operator<(const GenomeLink& l, int id)
{
    return l.id < id;
}