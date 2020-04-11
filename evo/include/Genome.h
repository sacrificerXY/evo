#pragma once

#include <functional>
#include <vector>
#include <string>

struct GenomeLinkIdGenerator;
struct Random;

struct GenomeLink {
    int from;
    int to;
    float weight;
    bool enabled;
    bool operator==(const GenomeLink& other) const
    {
        return from == other.from
            && to == other.to
            && weight == other.weight
            && enabled == other.enabled;
    }
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
    const Random& rand);
    
Genome copy(const Genome& g);
    
int add_hidden_node(Genome& g, const GenomeLinkIdGenerator& gen_id, const Random& rand);
void add_link(Genome& g, int id, const GenomeLink& link);
bool node_is_input(const Genome& g, int i);
bool node_is_hidden(const Genome& g, int i);
bool node_is_output(const Genome& g, int i);
bool node_is_valid(const Genome& g, int i);
bool link_is_valid(const Genome& g, int from, int to);
bool has_link(const Genome& g, int id);

std::string format(const Genome& g);

Genome mutate_add_link(
    const Genome& g,
    const GenomeLinkIdGenerator& gen_id,
    const Random& rand
);

//Genome mutate_add_link(const Genome& g, const GenomeLinkIdGenerator& gen_id, const std::function<float(void)>& gen_weight);