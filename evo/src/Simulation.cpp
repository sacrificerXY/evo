#include "Simulation.h"

#include <cassert>
#include <unordered_map>

#include <effolkronium/random.hpp>
// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

#include <fmt/core.h>

Simulation::Simulation(int num_inputs, int num_outputs)
    : num_inputs{ num_inputs + 1 }
    , num_outputs{ num_outputs }
{
    assert(num_inputs + num_outputs + 1 < MAX_NODES);
}

Genome Simulation::create_genome()
{
    Genome g(num_inputs, num_outputs);
    for(NodeIndex i = num_inputs; i < num_inputs + num_outputs; ++i) {
        const auto link = Link{ BIAS_INDEX, i };
        if(!links.contains(link)) {
            links[link] = id_count++;
        }
        const auto id = links[link];
        g.add_connection(id, link, 0, true);
    }
    return g;
}
// Genome Simulation::mutate(const Genome& g) const;
//

Genome Simulation::test_add_link(const Genome& g, NodeIndex from, NodeIndex to)
{
    const auto link = Link{ from, to };
    if(!links.contains(link)) {
        links[link] = id_count++;
    }
    const auto id = links[link];
    auto new_g = g;
    new_g.add_connection(id, link, 1, true);
    return new_g;
}
Genome Simulation::mutate_add_link(const Genome& g)
{
    auto from = Random::get<NodeIndex>(1, g.num_inputs + g.num_hidden - 1);
    if(from >= num_inputs) {
        fmt::print("  link HUMP\n");
        from += g.num_outputs;
    }
    auto to = Random::get<NodeIndex>(g.num_inputs, g.num_inputs + g.num_outputs + g.num_hidden - 1);
    fmt::print("link {} -> {}\n", from, to);
    auto link = Link{ from, to };
    if(links.contains(link)) {
        return g;
    }
    const auto id = get_id(link);
    auto new_g = g;
    new_g.add_connection(id, link, 88, true);
    return new_g;
}
Genome Simulation::test_add_node(const Genome& g, NodeIndex from, NodeIndex to)
{
    auto new_g = g;

    auto link = Link{ from, to };
    auto id = get_id(link);
    new_g.disable_connection(id);

    auto i = new_g.add_hidden_node();

    link = { BIAS_INDEX, i };
    id = get_id(link);
    new_g.add_connection(id, link, 9, true);

    link = { from, i };
    id = get_id(link);
    new_g.add_connection(id, link, -77, true);

    link = { i, to };
    id = get_id(link);
    new_g.add_connection(id, link, 77, true);

    return new_g;
}
Genome Simulation::mutate_add_node(const Genome& g)
{
    const auto i = Random::get<NodeIndex>(0, size(g.ids) - 1);
    fmt::print("chosen {} / {}\n", i, size(g.ids));
    auto old_link = g.links[i];
    fmt::print("mutate {} {} -> {}\n", g.ids[i], old_link.from, old_link.to);
    if(old_link.from == BIAS_INDEX)
        return g;
    fmt::print("  -- good\n");

    auto new_g = g;
    auto id = new_g.ids[i];
    new_g.disable_connection(id);

    auto new_i = new_g.add_hidden_node();

    {
        auto link = Link{ BIAS_INDEX, new_i };
        auto id = get_id(link);
        new_g.add_connection(id, link, 9, true);
    }
    {
        auto link = Link{ old_link.from, new_i };
        auto id = get_id(link);
        new_g.add_connection(id, link, -77, true);
    }
    {
        auto link = Link{ new_i, old_link.to };
        auto id = get_id(link);
        new_g.add_connection(id, link, 77, true);
    }

    return new_g;
}

Brain Simulation::create_brain(const Genome& g) const
{
    auto b = Brain(g.num_inputs, g.num_outputs, g.num_hidden);

    for(NodeIndex i = 0; i < size(g.links); ++i) {
        const auto link = g.links[i];
        const auto weight = g.weights[i];
        b.add_link(link.from, link.to, weight);
    }

    return b;
}

LinkId Simulation::get_id(Link link)
{
    if(!links.contains(link)) {
        links[link] = id_count++;
    }
    return links[link];
}