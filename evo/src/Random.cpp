#include "Random.h"


#include <doctest/doctest.h>
#include <effolkronium/random.hpp>
// get base random alias which is auto seeded and has static API and internal state
using rng = effolkronium::random_static;

#include "Genome.h"
#include "GenomeLinkIdGenerator.h"

auto Random::weight() const -> float
{
    return rng::get<float>(-weight_range, weight_range);
}

auto Random::from(const Genome& g) const -> int
{
    // start at 1 to skip bias
    auto i = rng::get<int>(1, g.num_inputs + g.num_hidden - 1);
    if (i >= g.num_inputs) i += g.num_outputs;
    REQUIRE(!node_is_output(g, i));
    return i;
}

auto Random::to(const Genome& g) const -> int
{
    const auto i = rng::get<int>(
        g.num_inputs, 
        g.num_inputs + g.num_outputs + g.num_hidden - 1);
    REQUIRE(!node_is_input(g, i));
    return i;
}

TEST_CASE("Random::from/to")
{
    auto rand = Random{};
    auto gen = GenomeLinkIdGenerator{};
    auto g = create_genome(2, 2, gen, rand);
    add_hidden_node(g, gen, rand);
    add_hidden_node(g, gen, rand);
    for (int i = 0; i < 100; ++i) {
        const auto f = rand.from(g);
        const auto t = rand.to(g);
        CHECK(link_is_valid(g, f, t));
    }
}