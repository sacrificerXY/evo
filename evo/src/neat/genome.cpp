#include "neat/genome.h"
#include "neat/_internal.h"

#include <algorithm>
#include <cassert>
#include <numeric>

#include <fmt/core.h>


namespace neat
{
    constexpr float random_weight() { return 1; };

    Genome create_genome(NodeIndex num_inputs, NodeIndex num_outputs)
    {
        fmt::print("genome(inputs={}+1 , outputs={})\n", num_inputs, num_outputs);
        num_inputs += 1; // for bias

        Nodes nodes;
        nodes.reserve(num_inputs);
        std::fill_n(back_inserter(nodes), num_inputs, Node{NodeType::INPUT});
        std::fill_n(back_inserter(nodes), num_outputs, Node{NodeType::OUTPUT});

        Links links;
        links.reserve(num_outputs);

        LinkIds linkIds;
        linkIds.reserve(num_outputs);

        fmt::print("connect bias to outputs\n");
        for (NodeIndex out_index = num_inputs; out_index < num_inputs+num_outputs; ++out_index) {
            internal::add_link(linkIds, links, Edge{bias_index, out_index}, random_weight());
        }

        return Genome{num_inputs, num_outputs, nodes, linkIds, links};
    }

    void mutate_add_link(Genome& genome, Edge edge, float weight)
    {
        internal::add_link(genome.linkIds, genome.links, edge, weight);
    }

    void mutate_split_link(Genome& genome, Edge edge)
    {
        auto& nodes = genome.nodes;
        auto& links = genome.links;
        assert(internal::contains(links, edge));
        fmt::print("split link ({} -> {})\n", edge.in, edge.out);

        auto link_it = std::find_if(
            begin(links), end(links),
            [edge] (const Link& link) {
                return link.edge == edge;
            }
        );

        link_it->enabled = false;
        fmt::print("disable link ({} -> {})\n", edge.in, edge.out);

        NodeIndex node_index = size(nodes);
        nodes.push_back({NodeType::HIDDEN});

        internal::add_link(genome.linkIds, links, Edge{bias_index, node_index}, random_weight());
        internal::add_link(genome.linkIds, links, Edge{edge.in, node_index}, 1);
        internal::add_link(genome.linkIds, links, Edge{node_index, edge.out}, link_it->weight);
    }

    std::vector<NodeIndex> get_output_node_indices(const Genome& genome)
    {
        std::vector<NodeIndex> indices(genome.num_outputs);
        std::iota(begin(indices), end(indices), genome.num_inputs);
        return indices;
    }


    std::string format_nodes(const Genome& genome)
    {
        std::string nodes = "---- nodes ------\n";
        for (NodeIndex i = 0; i < genome.nodes.size(); ++i) {
            std::string type;
            switch (genome.nodes[i].type) {
                case NodeType::INPUT: type = "input"; break;
                case NodeType::OUTPUT: type = "output"; break;
                case NodeType::HIDDEN: type = "hidden"; break;
            }
            fmt::format_to(
                back_inserter(nodes),
                "   {} {}\n",
                i, type
            );
        }
        return nodes;
    }

    std::string format_links(const Genome& genome)
    {
        std::string links = "---- links ------\n";
        for (NodeIndex i = 0; i < genome.linkIds.size(); ++i) {
            const auto& link = genome.links[i];
            fmt::format_to(
                back_inserter(links),
                " {} {:>3} ({} -> {}) w={}\n",
                link.enabled ? ' ' : '*', genome.linkIds[i], link.edge.in, link.edge.out, link.weight
            );
        }
        return links;
    }
}
