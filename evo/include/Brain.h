#pragma once

#include <vector>
#include <string>


struct Genome;

struct BrainLink {
    int from;
    int to;
    float weight;
};

struct Brain {
    int num_inputs;
    int num_outputs;
    int num_values;
    std::vector<BrainLink> links;
    std::vector<float> old_values;
    
    int genome_id;
};

Brain create_brain(const Genome& g);
std::vector<float> eval(Brain& b, std::vector<float> input);
void reset(Brain& b);
void prune_useless_links(Brain& b);

std::string format_links(const Brain& b);

