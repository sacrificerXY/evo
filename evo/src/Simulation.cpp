#include "Simulation.h"

#include <cassert>
#include <unordered_map>

#include <effolkronium/random.hpp>
// get base random alias which is auto seeded and has static API and internal
// state
using Random = effolkronium::random_static;

#include <fmt/core.h>

Simulation::Simulation(int num_inputs, int num_outputs) : num_inputs{num_inputs + 1}, num_outputs{num_outputs}
{
    assert(num_inputs + num_outputs + 1 < MAX_NODES);
}

Genome Simulation::create_genome()
{
    Genome g(num_inputs, num_outputs);
    for(NodeIndex i = num_inputs; i < num_inputs + num_outputs; ++i) {
        const auto link = Link{BIAS_INDEX, i};
        if(!links.contains(link)) {
            links[link] = id_count++;
        }
        const auto id = links[link];
        g.add_connection(id, link, Random::get(-2.f, 2.f), true);
    }
    return g;
}
Genome Simulation::mutate_add_link(const Genome& g)
{
    //fmt::print("mutate add link\n");
    auto from = Random::get<NodeIndex>(1, g.num_inputs + g.num_hidden - 1);
    if(from >= num_inputs) {
        //fmt::print("  link HUMP\n");
        from += g.num_outputs;
    }
    auto to = Random::get<NodeIndex>(g.num_inputs, g.num_inputs + g.num_outputs + g.num_hidden - 1);
    auto link = Link{from, to};
    const auto id = get_id(link);
    if (g.has_link(id)) return g;
    //if(!links.contains(link)) {
    //    return g;
    //}
    auto new_g = g;
    new_g.add_connection(id, link, Random::get(-2.f, 2.f), true);
    return new_g;
}

Genome Simulation::mutate_add_node(const Genome& g)
{
    //fmt::print("mutate add link\n");
    const auto i = Random::get<NodeIndex>(0, size(g.ids) - 1);
    //fmt::print("chosen {} / {}\n", i, size(g.ids));
    auto old_link = g.links[i];
    auto old_weight = g.weights[i];
    //fmt::print("mutate add node {} {} -> {}\n", g.ids[i], old_link.from, old_link.to);
    if(old_link.from == BIAS_INDEX)
        return g;
    //fmt::print("  -- good\n");

    auto new_g = g;
    auto id = new_g.ids[i];
    new_g.disable_connection(id);

    auto new_i = new_g.add_hidden_node();

    {
        auto link = Link{BIAS_INDEX, new_i};
        auto id = get_id(link);
        new_g.add_connection(id, link, Random::get(-2.f, 2.f), true);
    }
    {
        auto link = Link{old_link.from, new_i};
        auto id = get_id(link);
        new_g.add_connection(id, link, 1, true);
    }
    {
        auto link = Link{new_i, old_link.to};
        auto id = get_id(link);
        new_g.add_connection(id, link, old_weight, true);
    }

    return new_g;
}

Genome Simulation::mutate_weight(const Genome& g)
{
    //fmt::print("mutate weight\n");
    assert(size(g.links) > 0);
    const auto i = Random::get<int>(0, size(g.links) - 1);
    auto new_g = g;
    new_g.weights[i] += Random::get(-0.2f, 0.2f);
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