#pragma once

#include <string>
#include <vector>

#include "neat/common.h"


namespace neat
{
    struct Genome;
    
    struct Weight
    {
        NodeIndex index;
        float value;
    };
    
    using Weights = std::vector<std::vector<Weight>>;
    
    struct NeuralNetwork
    {
        NodeIndex num_inputs;
        std::vector<NodeIndex> hidden_nodes;
        Weights hidden_weights;
        std::vector<NodeIndex> output_nodes;
        Weights output_weights;
    };

    NeuralNetwork create_neural_network(const Genome& genome);
    std::vector<float> eval(const NeuralNetwork& net, std::vector<float> inputs);
    std::string format(const NeuralNetwork& net);
}
