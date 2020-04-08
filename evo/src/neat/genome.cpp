#include "neat/_internal.h"
#include "neat/genome.h"

#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <numeric>
#include <set>
#include <typeinfo>
#include <unordered_map>

#include <fmt/core.h>

namespace std
{
template <> struct hash<neat::Link> {
    auto operator()(const neat::Link& l) const
    {
        return (std::hash<decltype(l.from)>{}(l.from) << 16) & std::hash<decltype(l.to)>{}(l.to);
    }
};
}

namespace neat
{
bool operator==(const neat::Link& l, const neat::Link& r)
{
    return l.from == r.from && l.to == r.to;
}
LinkId get_insertion_point(const std::vector<LinkId>& ids, LinkId id)
{
    auto it = std::lower_bound(begin(ids), end(ids), id);
    return std::distance(begin(ids), it);
}

bool contains(const std::vector<LinkId>& ids, LinkId id)
{
    return std::binary_search(begin(ids), end(ids), id);
}

static auto existing_links = std::unordered_map<Link, LinkId>();
static auto id_count = LinkId{ 0 };

LinkId get_id(Link link)
{
    if(existing_links.contains(link))
        return existing_links[link];
    existing_links[link] = id_count;
    return id_count++;
}

LinkId test_get_id(Link link)
{
    const auto& l = existing_links;
    const auto i = id_count;
    if(l.contains(link))
        return l.at(link);
    return i;
}

float random_weight()
{
    return 1;
}

Genome Genome::create(unsigned int num_inputs_, unsigned int num_outputs_)
{
    fmt::print("Genome::create({}, {})\n", num_inputs_, num_outputs_);
    assert(num_inputs_ + 1 + num_outputs_ < std::numeric_limits<NodeIndex>::max());
    assert(num_inputs_ > 0);
    assert(num_outputs_ > 0);

    Genome g;
    g.num_inputs = num_inputs_ + 1;
    g.num_outputs = num_outputs_;
    for(NodeIndex i = 0; i < g.num_outputs; ++i) {
        g.add_link({ Node::BIAS_INDEX, i + g.num_inputs }, random_weight());
    }

    return g;
}
// Genome create_genome(NodeIndex num_inputs, NodeIndex num_outputs)
//{
//    fmt::print("create_genome({}, {})\n", num_inputs, num_outputs);
//
//    auto g = Genome{num_inputs + 1, num_outputs};
//    for (NodeIndex i = 0; i < num_outputs; ++i) {
//        g = add_connection(g, Node::BIAS_INDEX, i + g.num_inputs, random_weight());
//    }
//
//    return g;
//}
//
// Genome add_connection(const Genome&g, NodeIndex from, NodeIndex to, float weight)
//{
//    fmt::print("add_connection({} -> {})\n", from, to);
//    assert(get_node_type(g, from) != Node::Type::OUTPUT);
//    assert(get_node_type(g, to) != Node::Type::INPUT);
//
//    const auto link = Link{from, to};
//    const auto conn = Connection{
//        .id = get_id(link),
//        .link = link,
//        .weight = weight
//    };
//    assert(!g.connections.contains(conn));
//
//    return Genome
//    {
//        .num_inputs = g.num_inputs,
//        .num_outputs = g.num_outputs,
//        .num_hidden = g.num_hidden,
//        .connections = [&conns=g.connections,conn=std::move(conn)] () {
//            Connections new_conns(cbegin(conns), cend(conns));
//            auto s = size(new_conns);
//            new_conns.insert(std::move(conn));
//            assert(s < size(new_conns));
//            return new_conns;
//        }()
//    };
//}

void Genome::add_link(Link link, float weight)
{
    fmt::print("Genome::add_link({} -> {}, w={})\n", link.from, link.to, weight);
    assert(get_node_type(link.from) != Node::Type::OUTPUT);
    assert(get_node_type(link.to) != Node::Type::INPUT);
    assert(!has_link(link)); // link exists

    auto id = get_id(link);
    auto i = get_insertion_point(ids, id);
    ids.insert(std::next(begin(ids), i), id);
    links.insert(std::next(begin(links), i), link);
    weights.insert(std::next(begin(weights), i), weight);
}

NodeIndex Genome::add_hidden_node() {
    fmt::print("Genome::add_hidden_node()\n");
    assert(num_inputs + num_outputs + num_hidden < std::numeric_limits<NodeIndex>::max() - 1);
    return num_inputs + num_outputs + num_hidden++;
}

Node::Type Genome::get_node_type(NodeIndex i) const
{
    assert(i < num_inputs + num_outputs + num_hidden);
    if(i < num_inputs)
        return Node::Type::INPUT;
    else if(i < num_inputs + num_outputs)
        return Node::Type::OUTPUT;
    return Node::Type::HIDDEN;
}

bool Genome::has_link(Link link) const
{
    return contains(ids, test_get_id(link));
}

// Genome add_hidden_node(const Genome& g)
//{
//    assert(g.num_inputs + g.num_outputs + g.num_hidden < std::numeric_limits<NodeIndex>::max());
//    fmt::print("add_hidden_node()\n");
//    return Genome
//    {
//        .num_inputs = g.num_inputs,
//        .num_outputs = g.num_outputs,
//        .num_hidden = g.num_hidden + 1,
//        .connections = g.connections
//    };
//}
//
//
// Genome disable_connection(const Genome& g, NodeIndex from, NodeIndex to)
//{
//    //assert(g.connections.contains(
//}
//
//
// Node::Type get_node_type(const Genome& g, NodeIndex i)
//{
//    assert(0 <= i && i < g.num_inputs + g.num_outputs + g.num_hidden);
//
//    if (i < g.num_inputs) return Node::Type::INPUT;
//    else if (i < g.num_inputs + g.num_outputs) return Node::Type::OUTPUT;
//    return Node::Type::HIDDEN;
//}

//
// void Genome::add_connection(NodeIndex from, NodeIndex to)
//{
//
//    assert(from < num_inputs + 1 && from > num_inputs + num_outputs + 1);
//    const auto link = Link{from, to};
//    const auto conn = Connection{
//        get_id(link),
//        link,
//        random_weight()
//    };
//    assert(!connections.contains(conn));
//    connections.insert(conn);
//
//    fmt::print("Genome::add_connection({}, {}) id = {}\n", from, to, conn.id);
//}
//
// NodeIndex Genome::add_node(Node::Type type)
//{
//    assert(type == Node::Type::HIDDEN);
//    const auto index = num_inputs + num_outputs + num_hidden + 1;
//    num_hidden++;
//    fmt::print("Genome::add_node({}) {}\n", index, "hidden");
//    return index;
//}
//
bool operator<(const Connection& l, const Connection r)
{
    return l.id < r.id;
}

bool operator<(const Link& l, const Link& r)
{
    if(l.from < r.from)
        return true;
    return l.from == r.from && l.to < r.to;
}

// constexpr float random_weight() { return 1; };

// Genome create_genome(NodeIndex num_inputs, NodeIndex num_outputs)
//{
//    fmt::print("genome(inputs={}+1 , outputs={})\n", num_inputs, num_outputs);
//    num_inputs += 1; // for bias

//    Nodes nodes;
//    nodes.reserve(num_inputs);
//    std::fill_n(back_inserter(nodes), num_inputs, Node{NodeType::INPUT});
//    std::fill_n(back_inserter(nodes), num_outputs, Node{NodeType::OUTPUT});

//    Links links;
//    links.reserve(num_outputs);

//    LinkIds linkIds;
//    linkIds.reserve(num_outputs);

//    fmt::print("connect bias to outputs\n");
//    auto dependencies = decltype(Genome::dependencies)(size(nodes));
//    for (NodeIndex out_index = num_inputs; out_index < num_inputs+num_outputs; ++out_index) {
//        internal::add_link(linkIds, links, Edge{Node::BIAS_INDEX, out_index}, random_weight());
//        dependencies[out_index].push_back(Node::BIAS_INDEX);
//    }
//

//    return Genome{num_inputs, num_outputs, 0, 0, num_outputs, nodes, dependencies, linkIds, links};
//}

// void mutate_add_link(Genome& genome, Edge edge, float weight)
//{
//    internal::add_link(genome.linkIds, genome.links, edge, weight);
//    genome.num_enabled_links++;
//    genome.dependencies[edge.out].push_back(edge.in);
//}

// void mutate_split_link(Genome& genome, Edge edge)
//{
//    auto& nodes = genome.nodes;
//    auto& links = genome.links;
//    assert(internal::contains(links, edge));
//    fmt::print("split link ({} -> {})\n", edge.in, edge.out);

//    auto link_it = std::find_if(
//        begin(links), end(links),
//        [edge] (const Link& link) {
//            return link.edge == edge;
//        }
//    );

//    link_it->enabled = false;
//    fmt::print("disable link ({} -> {})\n", edge.in, edge.out);

//    NodeIndex node_index = size(nodes);
//    nodes.push_back({NodeType::HIDDEN});
//    genome.num_hidden++;
//    genome.dependencies[node_index].push_back(Node::BIAS_INDEX);

//    internal::add_link(genome.linkIds, links, Edge{Node::BIAS_INDEX, node_index}, random_weight());
//    internal::add_link(genome.linkIds, links, Edge{edge.in, node_index}, 1);
//    internal::add_link(genome.linkIds, links, Edge{node_index, edge.out}, link_it->weight);
//    genome.num_enabled_links += 2; // 1 disabled + 3 enabled
//    genome.dependencies[node_index].push_back(Node::BIAS_INDEX);
//    genome.dependencies[node_index].push_back(edge.in);
//    genome.dependencies[edge.out].push_back(node_index);
//}

// void mutate_add_memory(Genome& genome, Edge edge)
//{
//    auto& nodes = genome.nodes;
//    auto& links = genome.links;
//    assert(internal::contains(links, edge));
//    fmt::print("add memory ({} -> {})\n", edge.in, edge.out);
//
//    NodeIndex node_index = size(nodes);
//    nodes.push_back({NodeType::MEMORY});
//    genome.num_memory++;
//    genome.dependencies[node_index].push_back(Node::BIAS_INDEX);
//
//    internal::add_link(genome.linkIds, links, Edge{Node::BIAS_INDEX, node_index}, random_weight());
//    internal::add_link(genome.linkIds, links, Edge{edge.in, node_index}, random_weight());
//    internal::add_link(genome.linkIds, links, Edge{node_index, edge.out}, random_weight());
//    genome.num_enabled_links += 3;
//    genome.dependencies[node_index].push_back(Node::BIAS_INDEX);
//    genome.dependencies[node_index].push_back(edge.in);
//    genome.dependencies[edge.out].push_back(node_index);
//}

// std::vector<NodeIndex> get_output_node_indices(const Genome& genome)
//{
//    std::vector<NodeIndex> indices(genome.num_outputs);
//    std::iota(begin(indices), end(indices), genome.num_inputs);
//    return indices;
//}
//
// std::vector<Edge> get_available_links(const Genome& genome)
//{
//    std::vector<Edge> edges;
//    for (NodeIndex from = 1; from < size(genome.nodes); ++from) {
//        std::set<NodeIndex> nodes;
//        const auto from_type = genome.nodes[from].type;
//        if (from_type == NodeType::OUTPUT) {
//            for (NodeIndex to = genome.num_inputs + genome.num_outputs; to < size(genome.nodes); ++to) {
//                if (genome.nodes[to].type == NodeType::MEMORY) {
//                    nodes.insert(to);
//                }
//            }
//        }
//        else { // i-h-m can connect to o-h-m
//            for (NodeIndex to = genome.num_inputs; to < size(genome.nodes); ++to) {
//                if (from == to) continue; // self loop
//                nodes.insert(to);
//            }
//        }
//
//        for (const auto& link : genome.links) {
//            for (auto to : nodes) {
//                // edge exists
//                if (link.edge.in == from && link.edge.out == to)
//                    nodes.erase(to);
//                // a reverse edge exists
//                else if (link.edge.in == to && link.edge.out == from)
//                    nodes.erase(to);
//            }
//        }
//        for (auto to : nodes) {
//            edges.push_back(Edge{from, to});
//        }
//    }
//    return edges;
//}

// std::string format_nodes(const Genome& genome)
//{
//    std::string nodes = "---- nodes ------\n";
//    for (NodeIndex i = 0; i < genome.nodes.size(); ++i) {
//        std::string type;
//        switch (genome.nodes[i].type) {
//            case NodeType::INPUT: type = "input"; break;
//            case NodeType::OUTPUT: type = "output"; break;
//            case NodeType::HIDDEN: type = "hidden"; break;
//            case NodeType::MEMORY: type = "memory"; break;
//        }
//        fmt::format_to(
//            back_inserter(nodes),
//            "   {} {}\n",
//            i, type
//        );
//    }
//    return nodes;
//}

// std::string format_links(const Genome& genome)
//{
//    std::string links = "---- links ------\n";
//    for (NodeIndex i = 0; i < genome.linkIds.size(); ++i) {
//        const auto& link = genome.links[i];
//        fmt::format_to(
//            back_inserter(links),
//            " {} {:>3} ({} -> {}) w={}\n",
//            link.enabled ? ' ' : '*', genome.linkIds[i], link.edge.in, link.edge.out, link.weight
//        );
//    }
//    return links;
//}

std::string format(const Genome& g)
{
    std::string out = "---- genome ----\n";
    fmt::format_to(back_inserter(out), "  inputs = {}\n  outputs = {}\n  hidden = {}\n", g.num_inputs, g.num_outputs,
        g.num_hidden);
    fmt::format_to(back_inserter(out), "  -- conns {} ----\n", size(g.connections));
    for(NodeIndex i = 0; i < size(g.ids); ++i) {
        fmt::format_to(back_inserter(out), "    {:<3} ({} -> {})  w = {}\n", g.ids[i], g.links[i].from, g.links[i].to,
            g.weights[i]);
    }
    return out;
}
}
