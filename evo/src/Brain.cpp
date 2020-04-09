#include "Brain.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include <fmt/core.h>

Brain::Brain(NodeIndex num_inputs_, NodeIndex num_outputs_, NodeIndex num_hidden_)
    : num_inputs{num_inputs_}
    , num_outputs{num_outputs_}
    , num_values{num_inputs_ + num_outputs_ + num_hidden_}
    , past_values(num_values, 0.0f)
{
}
void Brain::add_link(NodeIndex from, NodeIndex to, float weight)
{
    static constexpr auto sort_func = [](const auto& l, const auto& r) {
        return (l.to < r.to) || ((l.to == r.to) && (l.from < r.from));
    };
    const auto link = Brain::Link{from, to, weight};
    assert(!std::binary_search(begin(links), end(links), link, sort_func));
    auto it = std::lower_bound(begin(links), end(links), link, sort_func);
    links.insert(it, link);
}

std::vector<float> Brain::eval(std::vector<float> input)
{
    assert(size(input) == num_inputs - 1);  // bias
    auto new_values = std::vector<float>(num_values, 0.0f);
    new_values[BIAS_INDEX] = 1;
    std::copy_n(begin(input), num_inputs - 1, begin(past_values) + 1);

    for(const auto& link : links) {
        new_values[link.to] += past_values[link.from] * link.weight;
    }
    for(int i = 0; i < num_values; ++i) {
        new_values[i] = std::tanh(new_values[i]);
    }
    past_values = new_values;
    return std::vector(begin(new_values) + num_inputs, begin(new_values) + num_inputs + num_outputs);
}

void Brain::reset_values()
{
    std::fill_n(begin(past_values), num_values, 0);
}

std::string Brain::format() const
{
    std::string out = "---- brain links ----\n";
    out += "  links\n";
    for(const auto& l : links) {
        const auto ls = fmt::format("{:>3} -> {:<3}", l.from, l.to);
        fmt::format_to(back_inserter(out), "    {} :: {}\n", ls, l.weight);
    }
    out += "  out: ";
    for(const auto& v : past_values) {
        fmt::format_to(back_inserter(out), "{} ", v);
    }
    out += '\n';
    return out;
}