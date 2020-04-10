#include "neat_types.h"

#include <algorithm>

#include <doctest/doctest.h>

#include "Id.h"


#define REQUIRE_VALID_NODE(g, i)\
{\
REQUIRE(i >= 0);\
REQUIRE(i < g.num_inputs + g.num_outputs + g.num_hidden);\
}

constexpr int BIAS_INDEX = 0;

Genome create_genome(const int num_inputs_, const int num_outputs_, GenomeLinkIdGenerator& gen_id)
{
    REQUIRE(num_inputs_ > 0);
    REQUIRE(num_outputs_ > 0);
    
    auto g = Genome {
        .id             =  Id<Genome>::get(),
        .num_inputs     = num_inputs_ + 1,
        .num_outputs    = num_outputs_,
        .num_hidden     = 0
    };
    
    for (auto i = g.num_inputs; i < g.num_inputs + g.num_outputs; ++i) {
        g.link_ids.push_back(gen_id(BIAS_INDEX, i));
        g.links.push_back(GenomeLink{
            .from = BIAS_INDEX,
            .to = i,
            .weight = 1,//rand
            .enabled = true
        });
    }
    
    return g;
}

TEST_CASE("create_genome")
{
    auto gen = GenomeLinkIdGenerator{};
    auto g = create_genome(3, 2, gen);
    
    REQUIRE(g.num_inputs == 3 + 1); // bias
    REQUIRE(g.num_outputs == 2);
    REQUIRE(g.num_hidden == 0);
    REQUIRE(g.link_ids.size() == 2);
    REQUIRE(g.links.size() == 2);
    REQUIRE(has_link(g, gen(BIAS_INDEX, 4)));
    REQUIRE(has_link(g, gen(BIAS_INDEX, 5)));
}


int add_hidden_node(Genome& g)
{
    int i = g.num_inputs + g.num_outputs + g.num_hidden++;
    REQUIRE(g.num_inputs + g.num_outputs + g.num_hidden - 1 == i);
    return i;
}

TEST_CASE("add_hidden_node")
{
    auto gen = GenomeLinkIdGenerator{};
    auto g = create_genome(1, 1, gen);
    auto index = add_hidden_node(g);
    REQUIRE(g.num_hidden == 1);
    REQUIRE(index == 3);
}

void add_link(Genome& g, int id, const GenomeLink& link)
{
    REQUIRE_FALSE(has_link(g, id));
    
    auto it = std::lower_bound(g.link_ids.begin(), g.link_ids.end(), id);
    if (it == g.link_ids.end()) {
        g.link_ids.push_back(id);
        g.links.push_back(link);
    }
    //REQUIRE_VALID_NODE(g, from);
    //REQUIRE_VALID_NODE(g, to);
    //const auto id = get_id(from, to);
    //REQUIRE(
}



bool is_node_input(const Genome& g, int i)
{
    REQUIRE_VALID_NODE(g, i);
    return i < g.num_inputs;
}
bool is_node_hidden(const Genome& g, int i)
{
    REQUIRE_VALID_NODE(g, i);
    return i >= g.num_inputs + g.num_outputs;
}
bool is_node_output(const Genome& g, int i)
{
    REQUIRE_VALID_NODE(g, i);
    return g.num_inputs <= i && i < g.num_inputs + g.num_outputs;
}
TEST_CASE("is_node checkers")
{
    auto gen = GenomeLinkIdGenerator{};
    auto g = create_genome(3, 2, gen);
    add_hidden_node(g); // 6
    add_hidden_node(g); // 7
    add_hidden_node(g); // 8
    
    SUBCASE("is_node_input")
    {
        // inputs
        REQUIRE         (is_node_input(g, 0));
        REQUIRE         (is_node_input(g, 1));
        REQUIRE         (is_node_input(g, 2));
        REQUIRE         (is_node_input(g, 3));
        // outputs
        REQUIRE_FALSE   (is_node_input(g, 4));
        REQUIRE_FALSE   (is_node_input(g, 5));
        // hidden
        REQUIRE_FALSE   (is_node_input(g, 6));
        REQUIRE_FALSE   (is_node_input(g, 7));
        REQUIRE_FALSE   (is_node_input(g, 8));
    }
    SUBCASE("is_node_hidden")
    {
        // inputs
        REQUIRE_FALSE   (is_node_hidden(g, 0));
        REQUIRE_FALSE   (is_node_hidden(g, 1));
        REQUIRE_FALSE   (is_node_hidden(g, 2));
        REQUIRE_FALSE   (is_node_hidden(g, 3));
        // outputs
        REQUIRE_FALSE   (is_node_hidden(g, 4));
        REQUIRE_FALSE   (is_node_hidden(g, 5));
        // hidden
        REQUIRE         (is_node_hidden(g, 6));
        REQUIRE         (is_node_hidden(g, 7));
        REQUIRE         (is_node_hidden(g, 8));
    }
    SUBCASE("is_node_output")
    {
        // inputs
        REQUIRE_FALSE   (is_node_output(g, 0));
        REQUIRE_FALSE   (is_node_output(g, 1));
        REQUIRE_FALSE   (is_node_output(g, 2));
        REQUIRE_FALSE   (is_node_output(g, 3));
        // outputs
        REQUIRE         (is_node_output(g, 4));
        REQUIRE         (is_node_output(g, 5));
        // hidden
        REQUIRE_FALSE   (is_node_output(g, 6));
        REQUIRE_FALSE   (is_node_output(g, 7));
        REQUIRE_FALSE   (is_node_output(g, 8));
    }
}



bool has_link(const Genome& g, int id)
{
    return std::binary_search(g.link_ids.begin(), g.link_ids.end(), id);
}