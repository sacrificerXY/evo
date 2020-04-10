#include "neat_types.h"

#include <algorithm>
#include <cmath>

#include <doctest/doctest.h>

#include "Id.h"

constexpr int BIAS_INDEX = 0;

Genome create_genome(const int num_inputs_, const int num_outputs_, const GenomeLinkIdGenerator& gen_id)
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
    
    CHECK(g.num_inputs == 3 + 1); // bias
    CHECK(g.num_outputs == 2);
    CHECK(g.num_hidden == 0);
    CHECK(g.link_ids.size() == 2);
    CHECK(g.links.size() == 2);
    CHECK(has_link(g, gen(BIAS_INDEX, 4)));
    CHECK(has_link(g, gen(BIAS_INDEX, 5)));
}


int add_hidden_node(Genome& g, const GenomeLinkIdGenerator& gen_id)
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



Brain create_brain(const Genome& g)
{
    auto b = Brain{
        .num_inputs = g.num_inputs,
        .num_outputs = g.num_outputs
    };
    for (const auto& g_link : g.links) {
        if (!g_link.enabled) continue;
        
        const auto b_link = BrainLink{
            .from = g_link.from,
            .to = g_link.to,
            .weight = g_link.weight
        };
        
        auto insertion_point = std::lower_bound(b.links.begin(), b.links.end(), b_link,
            [] (const auto& l, const auto& r) {
                return (l.to < r.to) || ((l.to == r.to) && (l.from < r.from));
        });
        
        b.links.insert(insertion_point, b_link);
    }
    b.num_values = b.links.size();
    b.old_values.resize(b.num_values, 0.0f);
    return b;
}

TEST_CASE("create_brain")
{
    auto gen = GenomeLinkIdGenerator{};
    auto g = create_genome(2, 1, gen);
    auto b = create_brain(g);
    CHECK(b.num_inputs == g.num_inputs);
    CHECK(b.num_outputs == g.num_outputs);
    CHECK(b.num_values == b.links.size());
    CHECK(b.old_values.size() == b.num_values);
    
    for (const auto& link : b.links) {
        CHECK(has_link(g, gen(link.from, link.to)));
    }
}

void reset(Brain& b)
{
    std::fill(b.old_values.begin(), b.old_values.end(), 0);
}


std::vector<float> eval(Brain& b, std::vector<float> input)
{
    REQUIRE(input.size() == b.num_inputs - 1); // bias
    
    auto new_values = std::vector<float>(b.num_values, 0.0f);
    new_values[BIAS_INDEX] = 1.0f; // bias
    
    // copy input into old_values so that they will be used during calculation of new_values
    std::copy_n(input.begin(), b.num_inputs - 1, b.old_values.begin() + 1);
    
    const auto calc_values = [&old_values = b.old_values, &new_values] (const auto& link) {
            new_values[link.to] = old_values[link.from] * link.weight;
    };
    std::for_each(b.links.begin(), b.links.end(), calc_values);
    
    // activate hidden
    {
        static const auto ReLU = [] (float x) { return (x < 0) ? 0 : x; };
        const auto start = new_values.begin() + b.num_inputs + b.num_outputs;
        const auto end = new_values.end();
        std::transform(start, end, start, ReLU);
    }
    // activate output
    {
        static const auto tanh = [] (float x) { return std::tanh(x); };
        const auto start = new_values.begin() + b.num_inputs;
        const auto end = new_values.begin() + b.num_inputs + b.num_outputs;
        std::transform(start, end, start, tanh);
    }
    // return output
    {
        const auto start = new_values.begin() + b.num_inputs;
        const auto end = new_values.begin() + b.num_inputs + b.num_outputs;
        return std::vector(start, end);
    }
}