#pragma once

#include <vector>

#include "Link.h"

class Genome
{
private:
    NodeIndex num_inputs;
    NodeIndex num_outputs;

public:
    std::vector<Link> links;
    std::vector<float> weights;
    std::vector<bool> enabled;

public:
    Genome(NodeIndex num_inputs, NodeIndex num_outputs);
    Genome(const Genome& g);
    Genome& operator=(Genome&&);
    void add_connection(LinkId id, Link link, float weight, bool enabled);
    void disable_connection(LinkId id);
    NodeIndex add_hidden_node();
    bool has_link(LinkId id) const;

    NodeType get_node_type(NodeIndex i) const;
    std::string format() const;

private:
    NodeIndex num_hidden = 0;
    std::vector<LinkId> ids;

    friend class Simulation;
};
