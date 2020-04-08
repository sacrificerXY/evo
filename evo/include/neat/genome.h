#pragma once

#include <set>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <vector>

#include "neat/common.h"

namespace neat
{

using NodeIndex = std::uint8_t;
struct Node {
    enum class Type { INPUT, OUTPUT, HIDDEN };
    Type type;
    constexpr static NodeIndex BIAS_INDEX = 0;
};

struct Link {
    NodeIndex from;
    NodeIndex to;
};
bool operator<(const Link& l, const Link& r);
using LinkId = std::uint16_t;

struct Connection {
public:
    using Id = std::uint16_t;

    Id id;
    Link link;
    float weight;
    bool enabled = true;
};
bool operator<(const Connection& l, const Connection r);
using Connections = std::set<Connection>;

struct Genome {
    NodeIndex num_inputs = 0;
    NodeIndex num_outputs = 0;
    NodeIndex num_hidden = 0;
    Connections connections;

    std::vector<LinkId> ids;
    std::vector<Link> links;
    std::vector<float> weights;
    std::vector<LinkId> disabled;

    void add_link(Link link, float weight);
    NodeIndex add_hidden_node();
    bool has_link(Link link) const;
    Node::Type get_node_type(NodeIndex i) const;
    static Genome create(unsigned int num_inputs, unsigned int num_outputs);
};

Genome create_genome(unsigned int num_inputs, int num_outputs);
Genome add_connection(const Genome& g, NodeIndex from, NodeIndex to, float weight);
Genome add_hidden_node(const Genome& g);
Genome disable_connection(const Genome& g, NodeIndex from, NodeIndex to);
Node::Type get_node_type(const Genome& g, NodeIndex i);

std::string format(const Genome& g);

namespace _7c233256_7479_42a7_afb0_b79dfd4ab264
{
    template <typename T>
    inline constexpr bool is_pod =
        std::is_move_assignable_v<T>&& std::is_move_constructible_v<T>&& std::is_standard_layout_v<T>;
    static_assert(is_pod<Node>);
    static_assert(is_pod<Link>);
    static_assert(is_pod<Connection>);
}
}
