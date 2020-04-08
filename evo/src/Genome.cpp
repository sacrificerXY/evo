#include "Genome.h"

#include <algorithm>
#include <cassert>

#include <fmt/core.h>

Genome::Genome(NodeIndex num_inputs, NodeIndex num_outputs)
    : num_inputs{ num_inputs }
    , num_outputs{ num_outputs }
{
}

Genome::Genome(const Genome& g)
    : num_inputs{ g.num_inputs }
    , num_outputs{ g.num_outputs }
    , links{ g.links }
    , weights{ g.weights }
    , enabled{ g.enabled }
    , num_hidden{ g.num_hidden }
    , ids{ g.ids }
{
}

Genome& Genome::operator=(Genome&& g)
{
    num_inputs = g.num_inputs;
    num_outputs = g.num_outputs;
    num_hidden = g.num_hidden;
    ids = std::move(g.ids);
    links = std::move(g.links);
    weights = std::move(g.weights);
    enabled = std::move(g.enabled);
    return *this;
}

void Genome::add_connection(LinkId id, Link link, float weight, bool enabled)
{
    fmt::print("Genome::add_connection({}, ({} -> {}), {}, {})\n", id, link.from, link.to, weight, enabled);

    assert(get_node_type(link.from) != NodeType::OUTPUT);
    assert(get_node_type(link.to) != NodeType::INPUT);
    // get insertion point
    const auto i = [& ids = this->ids, id]() {
        const auto b = std::cbegin(ids);
        const auto e = std::cend(ids);
        const auto it = std::lower_bound(b, e, id);
        return std::distance(b, it);
    }();
    if(i == std::size(ids)) {
        ids.push_back(id);
        links.push_back(link);
        weights.push_back(weight);
        this->enabled.push_back(enabled);
    } else {
        assert(ids[i] != id || links[id] != link);
        ids.insert(begin(ids) + i, id);
        links.insert(begin(links) + i, link);
        weights.insert(begin(weights) + i, weight);
        this->enabled.insert(begin(this->enabled) + i, enabled);
    }
}
void Genome::disable_connection(LinkId id)
{
    fmt::print("Genome::disable_connection({})\n", id);
    assert(std::binary_search(std::cbegin(ids), std::cend(ids), id));

    const auto i = [& ids = this->ids, id]() {
        const auto b = std::cbegin(ids);
        const auto e = std::cend(ids);
        const auto it = std::lower_bound(cbegin(ids), cend(ids), id);
        return std::distance(b, it);
    }();
    assert(ids[i] == id);

    enabled[i] = false;
    fmt::print("  link {} ({} -> {}) w={}\n", id, links[i].from, links[i].to, weights[i]);
}

NodeIndex Genome::add_hidden_node()
{
    assert(num_inputs + num_outputs + num_hidden + 1 < MAX_NODES);
    const auto i = num_inputs + num_outputs + num_hidden;
    num_hidden++;
    fmt::print("Genome::add_hidden_node() -- {}\n", i);
    return i;
}

NodeType Genome::get_node_type(NodeIndex i) const
{
    assert(i < num_inputs + num_outputs + num_hidden);
    if(i < num_inputs)
        return NodeType::INPUT;
    else if(i < num_inputs + num_outputs)
        return NodeType::OUTPUT;
    return NodeType::HIDDEN;
}

std::string Genome::format() const
{
    std::string out = "---- genome ----\n";
    fmt::format_to(
        back_inserter(out), "  inputs = {}\n  outputs = {}\n  hidden = {}\n", num_inputs, num_outputs, num_hidden);
    fmt::format_to(back_inserter(out), "  -- conns {} ----\n", size(ids));
    for(NodeIndex i = 0; i < size(ids); ++i) {
        const auto e = enabled[i] ? ' ' : 'x';
        fmt::format_to(
            back_inserter(out), "  {} {:<3} ({} -> {})  w = {}\n", e, ids[i], links[i].from, links[i].to, weights[i]);
    }
    return out;
}