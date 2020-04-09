#pragma once

#include <string>
#include <vector>

#include "Node.h"

class Brain
{
public:
    NodeIndex num_inputs;
    NodeIndex num_outputs;

    Brain(NodeIndex num_inputs, NodeIndex num_outputs, NodeIndex num_hidden);
    void add_link(NodeIndex from, NodeIndex to, NodeIndex weight);
    void eval(std::vector<float> input) const;
    std::string format() const;

private:
    struct Link {
        NodeIndex from;
        NodeIndex to;
        float weight;
    };

    NodeIndex num_values;
    std::vector<Link> links;
    std::vector<float> past_values;
};
