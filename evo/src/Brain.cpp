#include "Brain.h"

#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>
#include <set>

#include <doctest/doctest.h>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include "Genome.h"
#include "LinkIdGenerator.h"
#include "Random.h"

#include "Link.h"

constexpr int BIAS_INDEX = 0;


Brain create_brain(const Genome& g)
{
    // only include enabled links
    std::vector<BrainLink> links;
    for (const auto& g_link : g.links) {
        if (g_link.enabled) {
            links.push_back(BrainLink{
                .from = g_link.from,
                .to = g_link.to,
                .weight = g_link.weight
            });
        }
    }
    
    auto useful_nodes = get_useful_nodes(g.num_inputs, g.num_outputs, links);
    fmt::print("useful: {}\n", fmt::join(useful_nodes, " "));
    
    // remove useless links
    {
        const auto link_is_useless = [&useful_nodes](const auto& link) {
            return !useful_nodes.contains(link.from) || !useful_nodes.contains(link.to);
        };
        auto it = std::remove_if(links.begin(), links.end(), link_is_useless);
        links.erase(it, links.end());
    }
    
    std::sort(links.begin(), links.end(), [] (const auto& l, const auto& r) {
        return (l.to < r.to) || ((l.to == r.to) && (l.from < r.from));
    });
    
    // remap indices so that there no gaps
    // this allows us to use a vector instead of maps
    // 0 1 2 3 4 5 7 8 10 11 16 17 <--- this becomes...
    // 0 1 2 3 4 5 6 7 8  9  10 11 <--- this
    std::unordered_map<int, int> index_map;
    {
        auto it = useful_nodes.begin();
        int i = 0;
        while(it != useful_nodes.end()) {
            index_map[*it] = i;
            ++it;
            ++i;
        }
    }
    fmt::print("\n---- index map ----\n");
    for (auto [n, i] : std::map(index_map.begin(), index_map.end())) {
        fmt::print("{} -> {}\n", n, i);
    }
    
    for (auto& l : links) {
        l.from = index_map[l.from];
        l.to = index_map[l.to];
    }
    
    return Brain{
        .num_inputs = g.num_inputs,
        .num_outputs = g.num_outputs,
        .links = links
    };
}

//TEST_CASE("create_brain")
//{
//    auto rand = Random{};
//    
//    auto gen = GenomeLinkIdGenerator{};
//    auto g = create_genome(2, 1, gen, rand);
//    auto b = create_brain(g);
//    CHECK(b.num_inputs == g.num_inputs);
//    CHECK(b.num_outputs == g.num_outputs);
//    //CHECK(b.num_values == g.num_inputs + g.num_outputs + g.num_hidden);
//    //CHECK(b.old_values.size() == b.num_values);
//    
//    for (const auto& link : b.links) {
//        CHECK(has_link(g, gen(link.from, link.to)));
//    }
//}

void reset(Brain& b)
{
    std::fill(b.old_values.begin(), b.old_values.end(), 0);
}


// TODO eval(n_in, n_out, BrainLinks, input_vec)
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
        REQUIRE(b.num_inputs + b.num_outputs <= b.num_values);
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
    b.old_values = new_values;
    // return output
    {
        const auto start = new_values.begin() + b.num_inputs;
        const auto end = new_values.begin() + b.num_inputs + b.num_outputs;
        return std::vector(start, end);
    }
}


//TEST_CASE("eval brain")
//{
//    auto rand = Random{};
//    
//    auto gen = GenomeLinkIdGenerator{};
//    auto g = create_genome(3, 2, gen, rand);
//    {
//        auto h = add_hidden_node(g, gen, rand);
//        add_link(g, gen(1, h), GenomeLink{
//            .from = 1,
//            .to = h,
//            .weight = rand.weight(),
//            .enabled = true
//        });
//        add_link(g, gen(h, 4), GenomeLink{
//            .from = h,
//            .to = 4,
//            .weight = rand.weight(),
//            .enabled = true
//        });
//        
//    }
//    auto b = create_brain(g);
//    auto out = eval(b, {2, 3, 1});
//    out = eval(b, {2, 3, 1});
//    //out = eval(b, {1, 2, 3});
//    //out = eval(b, {1, 2, 3});
//    fmt::print("---- weights ----\n");
//    for (const auto& link : b.links) {
//        fmt::print("  {:>3} -> {:<3} == {}\n", link.from, link.to, link.weight);
//    }
//    fmt::print("---- values ----\n");
//    for (const auto& val : b.old_values) {
//        fmt::print("  {}\n", val );
//    }
//}


void prune_useless_links(Brain& b)
{
    auto useful_nodes = get_useful_nodes(b.num_inputs, b.num_outputs, b.links);
    
    fmt::print("---- useful_nodes ----\n");
    for (auto i : std::set(useful_nodes.begin(), useful_nodes.end())) {
        fmt::print("    {}\n", i);
    }
    fmt::print("\n");
    
    
    const auto link_is_useless = [&useful_nodes](const auto& link) {
        return !useful_nodes.contains(link.from) || !useful_nodes.contains(link.to);
    };
    auto it = std::remove_if(b.links.begin(), b.links.end(), link_is_useless);
    b.links.erase(it, b.links.end());
    
    std::map<int, int> index_map;
    for (int i = 0; i < useful_nodes.size(); ++i) {
        auto it = std::next(useful_nodes.begin(), i);
        index_map[*it] = i;
    }
    std::map im(index_map.begin(), index_map.end());
    
    // remap indices so that there no gaps
    // this allows us to use a vector instead of maps
    // 0 1 2 3 4 5 7 8 10 11 16 17 <--- this becomes...
    // 0 1 2 3 4 5 6 7 8  9  10 11 <--- this
    fmt::print("\n---- index map ----\n");
    for (auto [n, i] : im) {
        fmt::print("{} -> {}\n", n, i);
    }
    
}

std::string format_links(const Brain& b)
{
    std::string out = "---- BrainLinks ----\n";
    for (const auto& link : b.links) {
        //if (link.from == 0) continue;
        fmt::format_to(std::back_inserter(out),
            //"  {:>3} -> {:<3} {}\n",
            "  {:>3} -> {:<3}\n",
            //"{} {} {}\n",
            link.from, link.to, link.weight
        );
    }
    return out;
}