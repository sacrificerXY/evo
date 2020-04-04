#include "neat.h"

#include <algorithm>
#include <utility>
#include <cassert>
#include <functional>

#include <fmt/core.h>
#include <fmt/ranges.h>

namespace neat
{
    using Nodes = decltype(Genome::nodes);
    using LinkIds = decltype(Genome::linkIds);
    using Links = decltype(Genome::links);
    constexpr NodeIndex bias_index = 0;
    
    // cpp forward declarations
    
    LinkId get_id(Edge edge);
    bool contains(const Links& links, Edge edge);
    
    // add link in the correct insertion order
    void add_link(LinkIds& linkIds, Links& links, Edge edge, float weight);
    constexpr float random_weight() { return 1; };

    // definitions
    
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
            add_link(linkIds, links, Edge{bias_index, out_index}, random_weight());
        }
        
        return Genome{nodes, linkIds, links};
    }
    
    
    void mutate_add_link(Genome& genome, Edge edge, float weight)
    {
        add_link(genome.linkIds, genome.links, edge, weight);
    }
    
    void add_link(LinkIds& linkIds, Links& links, Edge edge, float weight)
    {
        assert(edge.in != edge.out);
        assert(not contains(links, edge));
        assert(not contains(links, {edge.out, edge.in}));
        fmt::print("add link ({} -> {}) w={}\n", edge.in, edge.out, weight);
        
        auto id_begin = cbegin(linkIds);
        auto id_end = cend(linkIds);
        auto id = get_id(edge);
        auto insert_index = std::distance(
            id_begin,
            std::lower_bound(id_begin, id_end, id)
        );
        linkIds.emplace(next(id_begin, insert_index), id);
        links.emplace(
            next(begin(links), insert_index),
            Link{edge, weight, true}
        );
    }
    
    
    void mutate_split_link(Genome& genome, Edge edge)
    {
        auto& nodes = genome.nodes;
        auto& links = genome.links;
        assert(contains(links, edge));
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
        
        add_link(genome.linkIds, links, Edge{bias_index, node_index}, random_weight());
        add_link(genome.linkIds, links, Edge{edge.in, node_index}, 1);
        add_link(genome.linkIds, links, Edge{node_index, edge.out}, link_it->weight);
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
                " {} {} ({} -> {}) w={}\n",
                link.enabled ? ' ' : '*', genome.linkIds[i], link.edge.in, link.edge.out, link.weight
            );
        }
        return links;
    }
    
    bool operator==(Edge edge1, Edge edge2)
    {
        return edge1.in == edge2.in && edge1.out == edge2.out;
    }
    
    
    // cpp only stuff
    bool contains(const Links& links, Edge edge)
    {
        return std::find_if(cbegin(links), cend(links), [edge] (const Link& link) {
            return link.edge == edge;
        }) != cend(links);
    }
    
    bool operator<(Edge edge1, Edge edge2)
    {
        if (edge1.in < edge2.in) {
//            std::cout << "edge cmp TRUE " << edge1 << ", " << edge2 << '\n';
            return true;
        }
        if (edge1.in == edge2.in and edge1.out < edge2.out) {
//            std::cout << "edge cmp TRUE " << edge1 << ", " << edge2 << '\n';
            return true;
        }
//        std::cout << "edge cmp FALSE " << edge1 << ", " << edge2 << '\n';
        return false;
    }
    // for tracking innovation number
    std::map<Edge, LinkId> edges;
    LinkId id_count = 0;
    LinkId get_id(Edge edge)
    {
        if (!edges.contains(edge)) {
            edges[edge] = id_count++;
        }
        return edges[edge];
    }
}

