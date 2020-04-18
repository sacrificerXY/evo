#include <doctest/doctest.h>

#include "Genome.h"
#include "GenomeLink.h"
#include "Id.h"
#include "Random.h"
#include "LinkIdGenerator.h"


TEST_CASE("add_link")
{
    auto id = Id<Genome>{};
    auto rand = Random{};
    
    auto gen = LinkIdGenerator{};
    auto g = create_genome(id.get(), 3, 2, gen, rand);
    
    auto link_id = gen.get(1, 4);
    CHECK_FALSE(has_link(g.links, link_id));
    add_link(g.links, GenomeLink{
        .id = link_id,
        .from = 1,
        .to = 4
    });
    CHECK(has_link(g.links, link_id));
    CHECK(g.links.back().from == 1);
    CHECK(g.links.back().to == 4);
}


TEST_CASE("disable_link")
{
    
    auto id = Id<Genome>{};
    auto rand = Random{};
    
    auto gen = LinkIdGenerator{};
    auto g = create_genome(id.get(), 3, 2, gen, rand);
    
    REQUIRE(g.links.front().enabled);
    disable_link(g.links, g.links.front().id);
    REQUIRE_FALSE(g.links.front().enabled);
}
