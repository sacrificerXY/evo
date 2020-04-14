#include "Genome.h"

#include <algorithm>

#include <doctest/doctest.h>

#include "Id.h"
#include "LinkIdGenerator.h"
#include "Random.h"

constexpr int BIAS_INDEX = 0;

Genome create_genome(
    const int id, 
    const int num_inputs_,
    const int num_outputs_, 
    LinkIdGenerator& link_id_gen,
    const Random& rand)
{
    REQUIRE(num_inputs_ > 0);
    REQUIRE(num_outputs_ > 0);
    
    auto g = Genome {
        .id             = id,
        .num_inputs     = num_inputs_ + 1,
        .num_outputs    = num_outputs_,
        .num_hidden     = 0
    };
    
    for (auto i = g.num_inputs; i < g.num_inputs + g.num_outputs; ++i) {
        const auto link_id = link_id_gen.get(BIAS_INDEX, i);
        add_link(g.links, GenomeLink{
            .id = link_id,
            .from = BIAS_INDEX,
            .to = i,
            .weight = rand.weight(),
            .enabled = true
        });
    }
    
    return g;
}
//
TEST_CASE("create_genome")
{
    auto id = Id<Genome>{};
    auto rand = Random{};
    
    auto link_id_gen = LinkIdGenerator{};
    auto g = create_genome(id.get(), 3, 2, link_id_gen, rand);
    
    CHECK(g.num_inputs == 3 + 1); // bias
    CHECK(g.num_outputs == 2);
    CHECK(g.num_hidden == 0);
    CHECK(g.links.size() == 2);
    CHECK(has_link(g.links, link_id_gen.test(BIAS_INDEX, 4)));
    CHECK(has_link(g.links, link_id_gen.test(BIAS_INDEX, 5)));
}

//
//Genome copy(const int id, const Genome& g)
//{
//    return Genome {
//        .id             = id,
//        .num_inputs     = g.num_inputs,
//        .num_outputs    = g.num_outputs,
//        .num_hidden     = g.num_hidden,
//        .link_ids       = g.link_ids,
//        .links          = g.links
//    };
//}
//
//
//TEST_CASE("Genome copy")
//{
//    auto id = Id<Genome>{};
//    auto rng = Random{};
//    auto gen = GenomeLinkIdGenerator{};
//    auto g1 = create_genome(id.get(), 3, 2, gen, rng);
//    auto g2 = copy(id.get(), g1); 
//    CHECK(g1.id != g2.id);
//    CHECK(g1.num_inputs == g2.num_inputs);
//    CHECK(g1.num_outputs == g2.num_outputs);
//    CHECK(g1.num_hidden == g2.num_hidden);
//    CHECK(g1.link_ids == g2.link_ids);
//    CHECK(g1.links == g2.links);
//}
//
//
//int add_hidden_node(Genome& g, const GenomeLinkIdGenerator& gen_id,
//    const Random& rand)
//{
//    int i = g.num_inputs + g.num_outputs + g.num_hidden++;
//    add_link(g, gen_id(BIAS_INDEX, i),
//        GenomeLink{
//            .from = BIAS_INDEX,
//            .to = i,
//            .weight = rand.weight(),
//            .enabled = true
//    });
//    return i;
//}
//
//TEST_CASE("add_hidden_node")
//{
//    auto id = Id<Genome>{};
//    auto rand = Random{};
//    
//    auto gen = GenomeLinkIdGenerator{};
//    auto g = create_genome(id.get(), 1, 1, gen, rand);
//    auto index = add_hidden_node(g, gen, rand);
//    CHECK(g.num_hidden == 1);
//    CHECK(index == 3);
//    CHECK(has_link(g, gen(BIAS_INDEX, index)));
//    CHECK(g.links.back().from == BIAS_INDEX);
//    CHECK(g.links.back().to == index);
//}
//
void add_link(std::vector<GenomeLink>& links, const GenomeLink& link)
{
    REQUIRE_FALSE(has_link(links, link));
    
    const auto insertion_point = std::lower_bound(links.begin(), links.end(), link);
     links.insert(insertion_point, link);
}
//
//TEST_CASE("add_link")
//{
//    auto id = Id<Genome>{};
//    auto rand = Random{};
//    
//    auto gen = GenomeLinkIdGenerator{};
//    auto g = create_genome(id.get(), 3, 2, gen, rand);
//    
//    auto link_id = gen(1, 4);
//    CHECK_FALSE(has_link(g, link_id));
//    add_link(g, link_id, GenomeLink{
//        .from = 1,
//        .to = 4
//    });
//    CHECK(has_link(g, link_id));
//    CHECK(g.links.back().from == 1);
//    CHECK(g.links.back().to == 4);
//}
//
//
//void disable_link(Genome& g, int id)
//{
//    REQUIRE(has_link(g, id));
//    const auto link_it = std::lower_bound(g.link_ids.begin(), g.link_ids.end(), id);
//    REQUIRE(*link_it == id);
//    const auto i = std::distance(g.link_ids.begin(), link_it);
//    g.links[i].enabled = false;
//}
//
//TEST_CASE("disable_link")
//{
//    
//    auto id = Id<Genome>{};
//    auto rand = Random{};
//    
//    auto gen = GenomeLinkIdGenerator{};
//    auto g = create_genome(id.get(), 3, 2, gen, rand);
//    
//    REQUIRE(g.links.front().enabled);
//    disable_link(g, g.link_ids.front());
//    REQUIRE_FALSE(g.links.front().enabled);
//}
//
//
//float get_link_weight(const Genome& g, int id)
//{
//    REQUIRE(has_link(g, id));
//    const auto link_it = std::lower_bound(g.link_ids.begin(), g.link_ids.end(), id);
//    REQUIRE(*link_it == id);
//    const auto i = std::distance(g.link_ids.begin(), link_it);
//    return g.links[i].weight;
//}
//
//bool node_is_input(const Genome& g, int i)
//{
//    REQUIRE(node_is_valid(g, i));
//    return i < g.num_inputs;
//}
//bool node_is_hidden(const Genome& g, int i)
//{
//    REQUIRE(node_is_valid(g, i));
//    return i >= g.num_inputs + g.num_outputs;
//}
//bool node_is_output(const Genome& g, int i)
//{
//    REQUIRE(node_is_valid(g, i));
//    return g.num_inputs <= i && i < g.num_inputs + g.num_outputs;
//}
//bool node_is_valid(const Genome& g, int i)
//{
//    return 0 <= i && i < g.num_inputs + g.num_outputs + g.num_hidden;
//}
//TEST_CASE("node query")
//{
//    auto id = Id<Genome>{};
//    auto rand = Random{};
//    
//    auto gen = GenomeLinkIdGenerator{};
//    auto g = create_genome(id.get(), 3, 2, gen, rand);
//    add_hidden_node(g, gen, rand); // 6
//    add_hidden_node(g, gen, rand); // 7
//    add_hidden_node(g, gen, rand); // 8
//    
//    SUBCASE("node_is_input")
//    {
//        // inputs
//        CHECK       (node_is_input(g, 0));
//        CHECK       (node_is_input(g, 1));
//        CHECK       (node_is_input(g, 2));
//        CHECK       (node_is_input(g, 3));
//        // outputs
//        CHECK_FALSE (node_is_input(g, 4));
//        CHECK_FALSE (node_is_input(g, 5));
//        // hidden
//        CHECK_FALSE (node_is_input(g, 6));
//        CHECK_FALSE (node_is_input(g, 7));
//        CHECK_FALSE (node_is_input(g, 8));
//    }
//    SUBCASE("node_is_hidden")
//    {
//        // inputs
//        CHECK_FALSE (node_is_hidden(g, 0));
//        CHECK_FALSE (node_is_hidden(g, 1));
//        CHECK_FALSE (node_is_hidden(g, 2));
//        CHECK_FALSE (node_is_hidden(g, 3));
//        // outputs
//        CHECK_FALSE (node_is_hidden(g, 4));
//        CHECK_FALSE (node_is_hidden(g, 5));
//        // hidden
//        CHECK       (node_is_hidden(g, 6));
//        CHECK       (node_is_hidden(g, 7));
//        CHECK       (node_is_hidden(g, 8));
//    }
//    SUBCASE("node_is_output")
//    {
//        // inputs
//        CHECK_FALSE (node_is_output(g, 0));
//        CHECK_FALSE (node_is_output(g, 1));
//        CHECK_FALSE (node_is_output(g, 2));
//        CHECK_FALSE (node_is_output(g, 3));
//        // outputs
//        CHECK       (node_is_output(g, 4));
//        CHECK       (node_is_output(g, 5));
//        // hidden
//        CHECK_FALSE (node_is_output(g, 6));
//        CHECK_FALSE (node_is_output(g, 7));
//        CHECK_FALSE (node_is_output(g, 8));
//    }
//    SUBCASE("node_is_valid")
//    {
//        CHECK       (node_is_valid(g, 0));
//        CHECK       (node_is_valid(g, 1));
//        CHECK       (node_is_valid(g, 2));
//        CHECK       (node_is_valid(g, 3));
//        CHECK       (node_is_valid(g, 4));
//        CHECK       (node_is_valid(g, 5));
//        CHECK       (node_is_valid(g, 6));
//        CHECK       (node_is_valid(g, 7));
//        CHECK       (node_is_valid(g, 8));
//        
//        CHECK_FALSE (node_is_valid(g, -1));
//        CHECK_FALSE (node_is_valid(g, 9));
//    }
//}
//
//
//bool link_is_valid(const Genome& g, int from, int to)
//{
//    return !(node_is_output(g, from) || node_is_input(g, to));
//}
bool has_link(const std::vector<GenomeLink>& links, int id)
{
    auto it = std::lower_bound(links.begin(), links.end(), id,
        [](const auto& link, int id) {
            return link.id < id;
        }
    );
    return it != links.end();
}
bool has_link(const std::vector<GenomeLink>& links, const GenomeLink& link)
{
    return has_link(links, link.id);
}
//
//
//bool link_is_enabled(const Genome& g, int id)
//{
//    REQUIRE(has_link(g, id));
//    const auto link_it = std::lower_bound(g.link_ids.begin(), g.link_ids.end(), id);
//    REQUIRE(*link_it == id);
//    const auto i = std::distance(g.link_ids.begin(), link_it);
//    return g.links[i].enabled;
//}
//TEST_CASE("link query")
//{
//    auto id = Id<Genome>{};
//    auto rand = Random{};
//    
//    auto gen = GenomeLinkIdGenerator{};
//    auto g = create_genome(id.get(), 1, 1, gen, rand);
//    auto i = 1;
//    auto o = 2;
//    auto h1 = add_hidden_node(g, gen, rand);
//    auto h2 = add_hidden_node(g, gen, rand);
//    SUBCASE("link_is_valid")
//    {
//        CHECK(link_is_valid(g, i, o));
//        CHECK(link_is_valid(g, i, h1));
//        CHECK(link_is_valid(g, h2, o));
//        CHECK(link_is_valid(g, h1, h2));
//        CHECK(link_is_valid(g, h1, h1)); // self loops
//        
//        CHECK_FALSE(link_is_valid(g, o, i));
//        CHECK_FALSE(link_is_valid(g, o, h1));
//        CHECK_FALSE(link_is_valid(g, h2, i));
//        CHECK_FALSE(link_is_valid(g, i, i)); // self loops
//        CHECK_FALSE(link_is_valid(g, o, o)); // self loops
//    }
//    SUBCASE("has_link")
//    {
//        CHECK(has_link(g, gen(BIAS_INDEX, o)));
//        
//        auto id = gen(i, o);
//        
//        CHECK_FALSE(has_link(g, id));
//        
//        add_link(g, id, {i, o});
//        CHECK(has_link(g, id));
//    }
//}
//
//#include <fmt/core.h>
//std::string format(const Genome& g)
//{
//    std::string out = fmt::format("---- Genome {} h={} ----\n", g.id, g.num_hidden);
//    for (int i = 0; i < g.link_ids.size(); i++) {
//        const auto id = g.link_ids[i];
//        const auto& link = g.links[i];
//        const auto e = link.enabled ? " " : "x";
//        fmt::format_to(std::back_inserter(out),
//            "{} {} {} {} {}\n",
//            id, link.from, link.to, link.weight, int(link.enabled)
//            //"  {} {:<3} {:>3} -> {:<3} {}\n",
//            //e, id, link.from, link.to, link.weight
//        );
//    }
//    return out;
//}
//
//
//Genome mutate_add_link(
//    const Genome& g,
//    const GenomeLinkIdGenerator& gen_id,
//    const Random& rand
//) {
//    auto new_g = copy(g);
//    
//    const auto from = rand.from(new_g);
//    const auto to = rand.to(new_g);
//    REQUIRE(link_is_valid(new_g, from, to));
//    
//    // only add if link does not exist
//    const auto id = gen_id(from, to);
//    if (!has_link(new_g, id)) {
//        add_link(new_g, id, GenomeLink{
//            .from = from,
//            .to = to,
//            .weight = rand.weight(),
//            .enabled = true
//        });
//    }
//    
//    return new_g;
//}
//
//
//Genome mutate_split_link(
//    const Genome& g,
//    const GenomeLinkIdGenerator& gen_id,
//    const Random& rand
//) {
//    auto new_g = copy(g);
//    
//    // choose random link to split
//    const auto from = rand.from(new_g);
//    const auto to = rand.to(new_g);
//    REQUIRE(link_is_valid(new_g, from, to));
//    
//    // only split if link exists
//    const auto id = gen_id(from, to);
//    if (has_link(new_g, id)) {
//        
//        // inherit enabled status of old link
//        const auto enabled = link_is_enabled(new_g, id);
//        const auto weight = get_link_weight(new_g, id);
//        
//        const auto h = add_hidden_node(new_g, gen_id, rand);
//        
//        
//        // from to hidden
//        add_link(new_g, gen_id(from, h), GenomeLink{
//            .from = from,
//            .to = h,
//            .weight = 1.0f,
//            .enabled = enabled
//        });
//        // hidden to to
//        add_link(new_g, gen_id(h, to), GenomeLink{
//            .from = h,
//            .to = to,
//            .weight = weight,
//            .enabled = enabled
//        });
//        
//        disable_link(new_g, id);
//    }
//    
//    return new_g;
//}
//
