#pragma once

#include <array>
#include <string>
#include <vector>

#include "neat/common.h"


namespace neat
{
    struct Genome;
    
    struct Weight
    {
        NodeIndex node;
        NodeIndex in;
        float value;
    };
    
    using Weights = std::vector<Weight>;
    
    struct Brain
    {
        // !!!!! use zero based indexing for each node type
        NodeIndex num_inputs;
        Weights weights;
        std::vector<float> memory_values;
    };

    Brain create_brain(const Genome& genome);
    std::vector<float> eval(const Brain& net, std::vector<float> inputs);
    std::string format(const Brain& net);
}
