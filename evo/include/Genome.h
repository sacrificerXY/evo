#pragma once

#include <functional>
#include <vector>
#include <string>

struct LinkIdGenerator;
struct Random;

struct GenomeLink {
    int id;
    int from;
    int to;
    float weight;
    bool enabled;
    bool operator==(const GenomeLink& other) const
    {
        return id == other.id
            && from == other.from
            && to == other.to
            && weight == other.weight
            && enabled == other.enabled;
    }
    
    bool operator<(const GenomeLink& other) const
    {
        return id < other.id;
    }
};

struct Genome {
    int id;
    int num_inputs;
    int num_outputs;
    int num_hidden;
    std::vector<GenomeLink> links;
};


Genome create_genome(
    int id,
    int num_inputs,
    int num_outputs,
    LinkIdGenerator& link_id_gen,
    const Random& rand);
    //const GenomeLinkIdGenerator& gen_id, 
    //const Random& rand);
    
    
//Genome copy(int new_id, const Genome& g);
//    
//int add_hidden_node(Genome& g, const GenomeLinkIdGenerator& gen_id, const Random& rand);
void add_link(std::vector<GenomeLink>& links, const GenomeLink& link);
//void disable_link(Genome& g, int id);
//float get_link_weight(const Genome& g, int id);
//bool node_is_input(const Genome& g, int i);
//bool node_is_hidden(const Genome& g, int i);
//bool node_is_output(const Genome& g, int i);
//bool node_is_valid(const Genome& g, int i);
//bool link_is_valid(const Genome& g, int from, int to);
//bool link_is_enabled(const Genome& g, int id);
bool has_link(const std::vector<GenomeLink>& links, int id);
bool has_link(const std::vector<GenomeLink>& links, const GenomeLink& link);
//
//std::string format(const Genome& g);
//
//Genome mutate_add_link(
//    const Genome& g,
//    const GenomeLinkIdGenerator& gen_id,
//    const Random& rand
//);
//
//Genome mutate_split_link(
//    const Genome& g,
//    const GenomeLinkIdGenerator& gen_id,
//    const Random& rand
//);

//Genome mutate_add_link(const Genome& g, const GenomeLinkIdGenerator& gen_id, const std::function<float(void)>& gen_weight);