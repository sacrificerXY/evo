#include "Simulation.h"

#include <cassert>
#include <unordered_map>

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
// NeuralNetwork Simulation::create_brain(const Genome& g) const;

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

LinkId Simulation::get_id(Link link)
{
    if(!links.contains(link)) {
        links[link] = id_count++;
    }
    return links[link];
}