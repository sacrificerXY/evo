#pragma once

#include <vector>

#include "Node.h"

class Brain
{
public:
    const NodeIndex num_inputs;
    const NodeIndex num_outputs;

    Brain(NodeIndex num_inputs, NodeIndex num_outputs, NodeIndex num_hidden);
    void add_link(NodeIndex from, NodeIndex to, NodeIndex weight);
    void eval(std::vector<float> input) const;

private:
    struct Link {
        NodeIndex from;
        NodeIndex to;
        float weight;
    };

    const NodeIndex num_values;
    std::vector<Link> links;
    std::vector<float> past_values;
};
