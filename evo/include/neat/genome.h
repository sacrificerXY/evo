#pragma once

#include <string>
#include <vector>

#include "neat/common.h"


namespace neat
{
    using LinkId = std::uint16_t;
    enum class NodeType { INPUT, OUTPUT, HIDDEN };

    struct Node
    {
        NodeType type;
    };

    struct Edge
    {
        NodeIndex in;
        NodeIndex out;
    };

    struct Link
    {
        Edge edge;
        float weight;
        bool enabled;
    };

    struct Genome
    {
        const NodeIndex num_inputs;
        const NodeIndex num_outputs;
        std::vector<Node> nodes;
        std::vector<LinkId> linkIds;
        std::vector<Link> links;
    };

    Genome create_genome(NodeIndex num_inputs, NodeIndex num_outputs);
    void mutate_add_link(Genome& genome, Edge edge, float weight);
    void mutate_split_link(Genome& genome, Edge edge);
    std::vector<NodeIndex> get_output_node_indices(const Genome& genome);
    std::string format_nodes(const Genome& genome);
    std::string format_links(const Genome& genome);
}
