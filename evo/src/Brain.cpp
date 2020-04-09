#include "Brain.h"

#include <algorithm>
#include <cassert>

#include <fmt/core.h>

Brain::Brain(NodeIndex num_inputs_, NodeIndex num_outputs_, NodeIndex num_hidden_)
    : num_inputs{ num_inputs_ }
    , num_outputs{ num_outputs_ }
    , num_values{ num_inputs_ + num_outputs_ + num_hidden_ }
    , past_values(num_values, 0.0f)
{
}
void Brain::add_link(NodeIndex from, NodeIndex to, NodeIndex weight)
{
    static constexpr auto sort_func = [](const auto& l, const auto& r) {
        return (l.to < r.to) || ((l.to == r.to) && (l.from < r.from));
    };
    const auto link = Brain::Link{ from, to, weight };
    assert(!std::binary_search(begin(links), end(links), link, sort_func));
    auto it = std::lower_bound(begin(links), end(links), link, sort_func);
    links.insert(it, link);
}
// void Brain::eval(std::vector<float> input) const;

std::string Brain::format() const
{
    std::string out = "---- brain links ----\n";
    for(const auto l : links) {
        const auto ls = fmt::format("{:>3} -> {:<3}", l.from, l.to);
        fmt::format_to(back_inserter(out), "    {} :: {}\n", ls, l.weight);
    }
    return out;
}