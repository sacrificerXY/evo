#pragma once

#include <vector>
#include <functional>

#include "GenomeLinkIdGenerator.h"


struct GenomeLink {
    int from;
    int to;
    float weight;
    bool enabled;
};

struct Genome {
    int id;
    int num_inputs;
    int num_outputs;
    int num_hidden;
    std::vector<int> link_ids;
    std::vector<GenomeLink> links;
};

Genome create_genome(int num_inputs, int num_outputs, 
    const GenomeLinkIdGenerator& gen_id, 
    const std::function<float(void)>& gen_weight);
    
int add_hidden_node(Genome& g, const GenomeLinkIdGenerator& gen_id, const std::function<float(void)>& gen_weight);
void add_link(Genome& g, int id, const GenomeLink& link);
bool node_is_input(const Genome& g, int i);
bool node_is_hidden(const Genome& g, int i);
bool node_is_output(const Genome& g, int i);
bool node_is_valid(const Genome& g, int i);
bool link_is_valid(const Genome& g, int from, int to);
bool has_link(const Genome& g, int id);

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
};

Brain create_brain(const Genome& g);
std::vector<float> eval(Brain& b, std::vector<float> input);
void reset(Brain& b);

