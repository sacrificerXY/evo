#pragma once

#include <vector>

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

Genome create_genome(int num_inputs, int num_outputs, GenomeLinkIdGenerator& gen_id);
int add_hidden_node(Genome& g);
void add_link(Genome& g, int id, int from, int to, float weight, bool enabled);

bool is_node_input(const Genome& g, int i);
bool is_node_hidden(const Genome& g, int i);
bool is_node_output(const Genome& g, int i);

bool has_link(const Genome& g, int id);

