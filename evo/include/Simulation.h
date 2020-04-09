#pragma once

#include <unordered_map>

#include "Brain.h"
#include "Genome.h"

class Simulation
{
public:
    const int num_inputs;
    const int num_outputs;
    Simulation(int num_inputs, int num_outputs);

    Genome create_genome();
    Brain create_brain(const Genome& g) const;
    
    Genome mutate_add_link(const Genome& g);
    Genome mutate_add_node(const Genome& g);
    Genome mutate_weight(const Genome& g);

private:
    LinkId id_count = 0;
    std::unordered_map<Link, LinkId> links;
    LinkId get_id(Link link);
};