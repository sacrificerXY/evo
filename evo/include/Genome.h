#pragma once

#include <functional>
#include <vector>
#include <string>

#include "GenomeLink.h"

struct LinkIdGenerator;
struct Random;


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
    
    
Genome copy(int new_id, const Genome& g);
//    
int add_hidden_node(Genome& g, LinkIdGenerator& link_id_gen, const Random& rand);

bool node_is_input(const Genome& g, int i);
bool node_is_hidden(const Genome& g, int i);
bool node_is_output(const Genome& g, int i);
bool node_is_valid(const Genome& g, int i);
bool link_is_valid(const Genome& g, int from, int to);
//
//std::string format(const Genome& g);
//
Genome mutate_add_link(
    const Genome& g,
    LinkIdGenerator& link_id_gen,
    const Random& rand,
    int new_id
);

Genome mutate_split_link(
    const Genome& g,
    LinkIdGenerator& link_id_gen,
    const Random& rand,
    int new_id
);

//Genome mutate_add_link(const Genome& g, const GenomeLinkIdGenerator& gen_id, const std::function<float(void)>& gen_weight);