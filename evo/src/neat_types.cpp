#include "neat_types.h"

#include <algorithm>

#include <doctest/doctest.h>

#include "Id.h"

constexpr int BIAS_INDEX = 0;

Genome create_genome(const int num_inputs_, const int num_outputs_)
{
    REQUIRE(num_inputs_ > 0);
    REQUIRE(num_outputs_ > 0);
    
    auto g = Genome {
        .id             =  Id<Genome>::get(),
        .num_inputs     = num_inputs_ + 1,
        .num_outputs    = num_outputs_,
        .num_hidden     = 0
    };
    REQUIRE(g.num_inputs == num_inputs_ + 1);
    REQUIRE(g.num_outputs == num_outputs_);
    REQUIRE(g.num_hidden == 0);
    
    std::generate_n(
        std::back_inserter(g.links),
        g.num_outputs,
        [out_index=g.num_inputs] () mutable {
            return GenomeLink{
                .id = 0,
                .from = BIAS_INDEX,
                .to = out_index++,
                .weight = 1,//rand
                .enabled = true
            };
        }
    );
    REQUIRE(g.links.size() == num_outputs_);
    
    return g;
}


int add_hidden_node(Genome& g)
{
    int i = g.num_inputs + g.num_outputs + g.num_hidden++;
    REQUIRE(g.num_inputs + g.num_outputs + g.num_hidden - 1 == i);
    return i;
}

void add_link(Genome& g, int from, int to, float weight, bool enabled)
{
    //REQUIRE(from > 0
}



bool is_node_input(const Genome& g, int i)
{
    REQUIRE(i >= 0);
    REQUIRE(i < g.num_inputs + g.num_outputs + g.num_hidden);
    return i < g.num_inputs;
}
bool is_node_hidden(const Genome& g, int i)
{
    REQUIRE(i >= 0);
    REQUIRE(i < g.num_inputs + g.num_outputs + g.num_hidden);
    return i >= g.num_inputs + g.num_outputs;
}
bool is_node_output(const Genome& g, int i)
{
    REQUIRE(i >= 0);
    REQUIRE(i < g.num_inputs + g.num_outputs + g.num_hidden);
    return g.num_inputs <= i && i < g.num_inputs + g.num_outputs;
}

TEST_CASE("is_node checkers")
{
    auto g = create_genome(3, 2);
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