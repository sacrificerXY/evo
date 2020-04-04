#include "neat/neural_network.h"
#include "neat/_internal.h"

#include <algorithm>
#include <unordered_map>

#include <fmt/core.h>


namespace neat
{
    NeuralNetwork create_neural_network(const Genome& genome)
    {
        const auto num_outputs = genome.num_outputs;
        const auto num_hidden = size(genome.nodes) - genome.num_inputs - genome.num_outputs;
        auto net = NeuralNetwork{
            genome.num_inputs,
            decltype(NeuralNetwork::hidden_nodes)(num_hidden),
            decltype(NeuralNetwork::hidden_weights)(num_hidden),
            decltype(NeuralNetwork::output_nodes)(num_outputs),
            decltype(NeuralNetwork::output_weights)(num_outputs),
        };

        struct Degree { NodeIndex node; NodeIndex count = 0; };

        auto degrees = std::vector<Degree>(num_hidden);
        auto graph = std::unordered_map<NodeIndex, std::vector<NodeIndex>>();
        auto hidden_weights_map = std::unordered_map<NodeIndex, std::vector<Weight>>(num_hidden);

        {
            auto degrees_map = std::unordered_map<NodeIndex, NodeIndex>(num_hidden);
            auto output_map = std::unordered_map<NodeIndex, NodeIndex>(num_outputs);

            for (const auto& link : genome.links) {
                if (!link.enabled) continue;
                const auto edge = link.edge;
                const auto type = genome.nodes[edge.out].type;
                // Loop through all enabled links

                if (type == NodeType::OUTPUT) {
                    if (!output_map.contains(edge.out)) {
                        const auto index = size(output_map);
                        net.output_nodes[index] = edge.out;
                        output_map[edge.out] = index;
                    }
                    net.output_weights[output_map[edge.out]].push_back({edge.in, link.weight});
                }
                else if (type == NodeType::HIDDEN) {
                    if (!degrees_map.contains(edge.out)) {
                        const auto index = size(degrees_map);
                        degrees[index].node = edge.out;
                        degrees_map[edge.out] = index;
                    }
                    if (genome.nodes[edge.in].type != NodeType::INPUT){
                        degrees[degrees_map[edge.out]].count++;
                        graph[edge.in].push_back(edge.out);
                    }
                    hidden_weights_map[edge.out].push_back({edge.in, link.weight});
                }
            }
        }

        auto hidden_map = std::unordered_map<NodeIndex, NodeIndex>(num_hidden);

        {
            auto end_degrees = end(degrees);
            while (size(hidden_map) != num_hidden) {
                auto zero_it = std::partition(begin(degrees), end_degrees,
                    [] (const Degree& degree) {
                        return degree.count != 0;
                });
                // loop through all degrees with zero count
                for (auto degree_it = zero_it; degree_it != end_degrees; ++degree_it) {
                    const auto index = size(hidden_map);
                    net.hidden_nodes[index] = degree_it->node;
                    hidden_map[degree_it->node] = index;
                    for (auto node : graph[degree_it->node]) {
                        std::find_if(begin(degrees), zero_it,
                            [node] (const Degree& degree) {
                                return degree.node == node;
                        })->count--;
                    }
                }
                end_degrees = zero_it;
            }
        }

        for (auto&& [node, weights] : hidden_weights_map) {
            net.hidden_weights[hidden_map[node]] = weights;
        }

        return net;
    }

    std::string format(const NeuralNetwork& net)
    {
        std::string out = "---- calc order ----\n";
        auto _format = [o=back_inserter(out)] (const std::vector<NodeIndex>& nodes, const Weights& weights) {
            for (NodeIndex i = 0; i < size(nodes); i++) {
                for (auto& weight : weights[i]) {
                    fmt::format_to(o,
                        "   ({} -> {}) w={}\n",
                        weight.index, nodes[i], weight.value
                    );
                }
            }
        };
        _format(net.hidden_nodes, net.hidden_weights);
        _format(net.output_nodes, net.output_weights);
        return out;
    }
}
