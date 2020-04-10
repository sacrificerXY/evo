#include "neat_types.h"

#include <algorithm>

#include <doctest/doctest.h>

#include "Id.h"

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
        const auto link_id = gen_id(BIAS_INDEX, i);
        add_link(g, link_id, 
            GenomeLink{
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


int add_hidden_node(Genome& g, GenomeLinkIdGenerator& gen_id)
{
    int i = g.num_inputs + g.num_outputs + g.num_hidden++;
    add_link(g, gen_id(BIAS_INDEX, i),
        GenomeLink{
            .from = BIAS_INDEX,
            .to = i,
            .weight = 2,
            .enabled = true
    });
    return i;
}

TEST_CASE("add_hidden_node")
{
    auto gen = GenomeLinkIdGenerator{};
    auto g = create_genome(1, 1, gen);
    auto index = add_hidden_node(g, gen);
    REQUIRE(g.num_hidden == 1);
    REQUIRE(index == 3);
    REQUIRE(has_link(g, gen(BIAS_INDEX, index)));
}

void add_link(Genome& g, int id, const GenomeLink& link)
{
    REQUIRE_FALSE(has_link(g, id));
    
    const auto id_insertion_point = std::lower_bound(g.link_ids.begin(), g.link_ids.end(), id);
    if (id_insertion_point == g.link_ids.end()) {
        g.link_ids.push_back(id);
        g.links.push_back(link);
    }
    else {
        const auto link_insertion_point = g.links.begin() + std::distance(g.link_ids.begin(), id_insertion_point);
        g.link_ids.insert(id_insertion_point, id);
        g.links.insert(link_insertion_point, link);
    }
}

TEST_CASE("add_link")
{
    auto gen = GenomeLinkIdGenerator{};
    auto g = create_genome(3, 2, gen);
    
    auto id = gen(1, 4);
    REQUIRE_FALSE(has_link(g, id));
    add_link(g, id, GenomeLink{
        .from = 1,
        .to = 4
    });
    REQUIRE(has_link(g, id));
    REQUIRE(g.links.back().from == 1);
    REQUIRE(g.links.back().to == 4);
}



bool node_is_input(const Genome& g, int i)
{
    REQUIRE(node_is_valid(g, i));
    return i < g.num_inputs;
}
bool node_is_hidden(const Genome& g, int i)
{
    REQUIRE(node_is_valid(g, i));
    return i >= g.num_inputs + g.num_outputs;
}
bool node_is_output(const Genome& g, int i)
{
    REQUIRE(node_is_valid(g, i));
    return g.num_inputs <= i && i < g.num_inputs + g.num_outputs;
}
bool node_is_valid(const Genome& g, int i)
{
    return 0 <= i && i < g.num_inputs + g.num_outputs + g.num_hidden;
}
TEST_CASE("node query")
{
    auto gen = GenomeLinkIdGenerator{};
    auto g = create_genome(3, 2, gen);
    add_hidden_node(g, gen); // 6
    add_hidden_node(g, gen); // 7
    add_hidden_node(g, gen); // 8
    
    SUBCASE("node_is_input")
    {
        // inputs
        REQUIRE         (node_is_input(g, 0));
        REQUIRE         (node_is_input(g, 1));
        REQUIRE         (node_is_input(g, 2));
        REQUIRE         (node_is_input(g, 3));
        // outputs
        REQUIRE_FALSE   (node_is_input(g, 4));
        REQUIRE_FALSE   (node_is_input(g, 5));
        // hidden
        REQUIRE_FALSE   (node_is_input(g, 6));
        REQUIRE_FALSE   (node_is_input(g, 7));
        REQUIRE_FALSE   (node_is_input(g, 8));
    }
    SUBCASE("node_is_hidden")
    {
        // inputs
        REQUIRE_FALSE   (node_is_hidden(g, 0));
        REQUIRE_FALSE   (node_is_hidden(g, 1));
        REQUIRE_FALSE   (node_is_hidden(g, 2));
        REQUIRE_FALSE   (node_is_hidden(g, 3));
        // outputs
        REQUIRE_FALSE   (node_is_hidden(g, 4));
        REQUIRE_FALSE   (node_is_hidden(g, 5));
        // hidden
        REQUIRE         (node_is_hidden(g, 6));
        REQUIRE         (node_is_hidden(g, 7));
        REQUIRE         (node_is_hidden(g, 8));
    }
    SUBCASE("node_is_output")
    {
        // inputs
        REQUIRE_FALSE   (node_is_output(g, 0));
        REQUIRE_FALSE   (node_is_output(g, 1));
        REQUIRE_FALSE   (node_is_output(g, 2));
        REQUIRE_FALSE   (node_is_output(g, 3));
        // outputs
        REQUIRE         (node_is_output(g, 4));
        REQUIRE         (node_is_output(g, 5));
        // hidden
        REQUIRE_FALSE   (node_is_output(g, 6));
        REQUIRE_FALSE   (node_is_output(g, 7));
        REQUIRE_FALSE   (node_is_output(g, 8));
    }
    SUBCASE("node_is_valid")
    {
        REQUIRE         (node_is_valid(g, 0));
        REQUIRE         (node_is_valid(g, 1));
        REQUIRE         (node_is_valid(g, 2));
        REQUIRE         (node_is_valid(g, 3));
        REQUIRE         (node_is_valid(g, 4));
        REQUIRE         (node_is_valid(g, 5));
        REQUIRE         (node_is_valid(g, 6));
        REQUIRE         (node_is_valid(g, 7));
        REQUIRE         (node_is_valid(g, 8));
        
        REQUIRE_FALSE   (node_is_valid(g, -1));
        REQUIRE_FALSE   (node_is_valid(g, 9));
    }
}


bool link_is_valid(const Genome& g, int from, int to)
{
    return !(node_is_output(g, from) || node_is_input(g, to));
}
bool has_link(const Genome& g, int id)
{
    return std::binary_search(g.link_ids.begin(), g.link_ids.end(), id);
}
//TEST_CASE("link query")
//{
//    auto gen = GenomeLinkIdGenerator{};
//    auto g = create_genome(3, 2);
//    auto h1 = add_hidden_node(g);
//    auto h2 = add_hidden_node(g);
//    auto h2 = add_hidden_node(g);
//    REQUIRE_FALSE(has_link(g, gen(
//}