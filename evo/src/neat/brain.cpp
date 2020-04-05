#include "neat/brain.h"
#include "neat/_internal.h"

#include <algorithm>
#include <cassert>
#include <unordered_map>

#include <fmt/core.h>


namespace neat
{
    struct GraphNode {
        NodeIndex degree = 0;
        NodeIndexs dependencies;
    };
    using DependencyGraph = std::vector<GraphNode>;

    NodeIndexs kahns_sort(DependencyGraph&& graph)
    {
        const auto num_nodes = size(graph);
        NodeIndexs order;
        order.reserve(num_nodes);
        std::vector<bool> done(num_nodes, false);
        for (NodeIndex i = 0; i < num_nodes; ++i) {
            fmt::print("{} degree={}\n", i, graph[i].degree);
            for (auto n : graph[i].dependencies) {
                fmt::print("  - {}\n", n);
            }
        }

        auto end = num_nodes;
        while (size(order) != num_nodes) {
            for (NodeIndex i = 0; i < end; ++i) {
                if (!done[i] && graph[i].degree == 0) {
                    order.push_back(i);
                    for (auto n : graph[i].dependencies) {
                        assert(n < num_nodes);
                        graph[n].degree--;
                    }
                    done[i] = true;
                }
            }
        }

        return order;
    }

    Brain create_brain(const Genome& genome)
    {
        assert(genome.num_inputs - 1 > 0); // excluding bias
        assert(genome.num_outputs > 0);

        const auto nodes = genome.nodes;
        const auto num_inputs = genome.num_inputs;
        const auto num_outputs = genome.num_outputs;
        const auto num_hidden = genome.num_hidden;
        const auto num_memory = genome.num_memory;
        const auto num_nodes = num_inputs + num_outputs + num_hidden + num_memory;

        fmt::print("i: {}\n", num_inputs);
        fmt::print("o: {}\n", num_outputs);
        fmt::print("h: {}\n", num_hidden);
        fmt::print("m: {}\n", num_memory);

        auto node_map = NodeIndexs(num_nodes);
        auto node_map_zero = NodeIndexs(num_nodes);

        // map input and output
        {
            for (NodeIndex i = 0; i < num_inputs; ++i) {
                node_map[i] = i;
                node_map_zero[i] = i;
            }
            for (NodeIndex i = 0; i < num_outputs; ++i) {
                node_map[num_inputs + i] = num_inputs + num_memory + num_hidden + i;
                node_map_zero[num_inputs + i] = i;
            }
        }

        // map all hidden and memory nodes
        for (NodeIndex i = num_inputs + num_outputs, h = 0, m = 0; i < num_nodes; ++i) {
            switch (genome.nodes[i].type) {
                case NodeType::HIDDEN:
                    node_map[i] = num_inputs + num_memory + h;
                    node_map_zero[i] = h;
                    h++;
                    break;
                case NodeType::MEMORY:
                    node_map[i] = num_inputs + m;
                    node_map_zero[i] = m;
                    m++;
                    break;
                default: assert(false);
            }
        }

        fmt::print("---- node map ----\n");
        for (NodeIndex i = 0; i < num_nodes; ++i) {
            fmt::print("   {} -- {}\n", i, node_map[i]);
        }

        auto brain = Brain{
            num_outputs,
            decltype(Brain::weights)(),
            decltype(Brain::memory_values)(num_memory, NodeIndex{0}),
        };
        brain.weights.reserve(genome.num_enabled_links);


        auto graph = DependencyGraph(num_hidden);
        auto hidden_weights = std::vector<Weights>(num_hidden);
        auto output_weights = std::vector<Weights>(num_outputs);
        for (const auto& link : genome.links) {
            if (!link.enabled) continue;
            const auto edge = link.edge;
            const auto zero_edge = Edge{node_map_zero[edge.in], node_map_zero[edge.out]};
            switch (genome.nodes[edge.out].type) {
                case NodeType::OUTPUT: {
                    output_weights[zero_edge.out].push_back({node_map[edge.out], node_map[edge.in], link.weight});
                    break;
                }
                case NodeType::HIDDEN: {
                    if (genome.nodes[edge.in].type != NodeType::INPUT) {
                        fmt::print("link ({} -> {})\n", edge.in, edge.out);
                        graph[zero_edge.out].degree++;
                        graph[zero_edge.in].dependencies.push_back(zero_edge.out);
                    }
                    hidden_weights[zero_edge.out].push_back({node_map[edge.out], node_map[edge.in], link.weight});
                    break;
                }
                default: assert(false);
            }
        }

        auto hidden_node_order = kahns_sort(std::move(graph));
        for (NodeIndex i = 0; i < num_hidden; ++i) {
            auto& w = hidden_weights[hidden_node_order[i]];
            brain.weights.insert(
                end(brain.weights),
                make_move_iterator(begin(w)),
                make_move_iterator(end(w))
            );
        }
        for (NodeIndex i = 0; i < num_outputs; ++i) {
            auto& w = output_weights[i];
            brain.weights.insert(
                end(brain.weights),
                make_move_iterator(begin(w)),
                make_move_iterator(end(w))
            );
        }

        return brain;
    }

    std::vector<float> eval(const Brain& brain, std::vector<float> inputs)
    {
        const auto num_outputs = brain.num_outputs;
        const auto num_memory = size(brain.memory_values);
        auto values = std::vector<float>(1, 1); // add bias
        values.insert(end(values), begin(inputs), end(inputs));
        values.insert(end(values), begin(brain.memory_values), end(brain.memory_values));

        {
            auto n = brain.weights.front().node;
            auto w = cbegin(brain.weights);
            while (w != cend(brain.weights)) {
                fmt::print("calc start\n");
                float sum = 0;
                while (w != cend(brain.weights) && w->node == n) {
                    fmt::print("w.n={}  n={}\n", w->node, n);
                    sum += values[w->in] * w->value;
                    ++w;
                }
                // activation
                values.push_back(sum);
                ++n;
            }
        }

        fmt::print("values    ");
        for (NodeIndex i = 0; i < size(values); ++i) {
            fmt::print("  {:<3} {:<5}\n", i, values[i]);
        }
        fmt::print("\n");


        return std::vector(end(values) - num_outputs - num_memory, end(values));
    }

    std::string format(const Brain& brain)
    {
        std::string out = "---- calc order ----\n";
        for (const auto& w : brain.weights) {
            fmt::format_to(back_inserter(out),
                "{:<3} {:<3} {}\n",
                w.in, w.node, w.value
            );
        }
        return out;
    }
}
