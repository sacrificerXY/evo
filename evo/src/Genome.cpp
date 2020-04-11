#include "Genome.h"

#include <algorithm>

#include <doctest/doctest.h>

#include "Id.h"
#include "GenomeLinkIdGenerator.h"

constexpr int BIAS_INDEX = 0;

Genome create_genome(const int num_inputs_, const int num_outputs_, 
    const GenomeLinkIdGenerator& gen_id,
    const std::function<float(void)>& gen_weight = [](){ return 0.0f; })
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
                .weight = gen_weight(),//rand
                .enabled = true
        });
    }
    
    return g;
}

TEST_CASE("create_genome")
{
    auto gen = GenomeLinkIdGenerator{};
    auto g = create_genome(3, 2, gen);
    
    CHECK(g.num_inputs == 3 + 1); // bias
    CHECK(g.num_outputs == 2);
    CHECK(g.num_hidden == 0);
    CHECK(g.link_ids.size() == 2);
    CHECK(g.links.size() == 2);
    CHECK(has_link(g, gen(BIAS_INDEX, 4)));
    CHECK(has_link(g, gen(BIAS_INDEX, 5)));
}


int add_hidden_node(Genome& g, const GenomeLinkIdGenerator& gen_id,
    const std::function<float(void)>& gen_weight = [](){ return 0.0f; })
{
    int i = g.num_inputs + g.num_outputs + g.num_hidden++;
    add_link(g, gen_id(BIAS_INDEX, i),
        GenomeLink{
            .from = BIAS_INDEX,
            .to = i,
            .weight = gen_weight(),
            .enabled = true
    });
    return i;
}

TEST_CASE("add_hidden_node")
{
    auto gen = GenomeLinkIdGenerator{};
    auto g = create_genome(1, 1, gen);
    auto index = add_hidden_node(g, gen);
    CHECK(g.num_hidden == 1);
    CHECK(index == 3);
    CHECK(has_link(g, gen(BIAS_INDEX, index)));
    CHECK(g.links.back().from == BIAS_INDEX);
    CHECK(g.links.back().to == index);
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
    CHECK_FALSE(has_link(g, id));
    add_link(g, id, GenomeLink{
        .from = 1,
        .to = 4
    });
    CHECK(has_link(g, id));
    CHECK(g.links.back().from == 1);
    CHECK(g.links.back().to == 4);
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
        CHECK       (node_is_input(g, 0));
        CHECK       (node_is_input(g, 1));
        CHECK       (node_is_input(g, 2));
        CHECK       (node_is_input(g, 3));
        // outputs
        CHECK_FALSE (node_is_input(g, 4));
        CHECK_FALSE (node_is_input(g, 5));
        // hidden
        CHECK_FALSE (node_is_input(g, 6));
        CHECK_FALSE (node_is_input(g, 7));
        CHECK_FALSE (node_is_input(g, 8));
    }
    SUBCASE("node_is_hidden")
    {
        // inputs
        CHECK_FALSE (node_is_hidden(g, 0));
        CHECK_FALSE (node_is_hidden(g, 1));
        CHECK_FALSE (node_is_hidden(g, 2));
        CHECK_FALSE (node_is_hidden(g, 3));
        // outputs
        CHECK_FALSE (node_is_hidden(g, 4));
        CHECK_FALSE (node_is_hidden(g, 5));
        // hidden
        CHECK       (node_is_hidden(g, 6));
        CHECK       (node_is_hidden(g, 7));
        CHECK       (node_is_hidden(g, 8));
    }
    SUBCASE("node_is_output")
    {
        // inputs
        CHECK_FALSE (node_is_output(g, 0));
        CHECK_FALSE (node_is_output(g, 1));
        CHECK_FALSE (node_is_output(g, 2));
        CHECK_FALSE (node_is_output(g, 3));
        // outputs
        CHECK       (node_is_output(g, 4));
        CHECK       (node_is_output(g, 5));
        // hidden
        CHECK_FALSE (node_is_output(g, 6));
        CHECK_FALSE (node_is_output(g, 7));
        CHECK_FALSE (node_is_output(g, 8));
    }
    SUBCASE("node_is_valid")
    {
        CHECK       (node_is_valid(g, 0));
        CHECK       (node_is_valid(g, 1));
        CHECK       (node_is_valid(g, 2));
        CHECK       (node_is_valid(g, 3));
        CHECK       (node_is_valid(g, 4));
        CHECK       (node_is_valid(g, 5));
        CHECK       (node_is_valid(g, 6));
        CHECK       (node_is_valid(g, 7));
        CHECK       (node_is_valid(g, 8));
        
        CHECK_FALSE (node_is_valid(g, -1));
        CHECK_FALSE (node_is_valid(g, 9));
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

TEST_CASE("link query")
{
    auto gen = GenomeLinkIdGenerator{};
    auto g = create_genome(1, 1, gen);
    auto i = 1;
    auto o = 2;
    auto h1 = add_hidden_node(g, gen);
    auto h2 = add_hidden_node(g, gen);
    SUBCASE("link_is_valid")
    {
        CHECK(link_is_valid(g, i, o));
        CHECK(link_is_valid(g, i, h1));
        CHECK(link_is_valid(g, h2, o));
        CHECK(link_is_valid(g, h1, h2));
        CHECK(link_is_valid(g, h1, h1)); // self loops
        
        CHECK_FALSE(link_is_valid(g, o, i));
        CHECK_FALSE(link_is_valid(g, o, h1));
        CHECK_FALSE(link_is_valid(g, h2, i));
        CHECK_FALSE(link_is_valid(g, i, i)); // self loops
        CHECK_FALSE(link_is_valid(g, o, o)); // self loops
    }
    SUBCASE("has_link")
    {
        CHECK(has_link(g, gen(BIAS_INDEX, o)));
        
        auto id = gen(i, o);
        
        CHECK_FALSE(has_link(g, id));
        
        add_link(g, id, {i, o});
        CHECK(has_link(g, id));
    }
}

