
#include <algorithm>
#include <array>
#include <cassert>
#include <vector>

#include <fmt/core.h>

#include "Simulation.h"

#include <effolkronium/random.hpp>
// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

struct Unit {
    Genome genome;
    Brain brain;
    float score = 0.f;
};

int main()
{
    constexpr int epochs = 10000;
    constexpr int pops = 50;
    constexpr int top = pops / 2;
    constexpr int rand_pops = 0;
    constexpr int tests = 20;
    Simulation sim(2, 1);

    auto units = std::vector<Unit>();
    for(int i = 0; i < pops + rand_pops; i++) {
        auto g = sim.create_genome();
        g = sim.mutate_add_link(g);
        g = sim.mutate_add_link(g);
        g = sim.mutate_add_link(g);
        g = sim.mutate_add_link(g);
        g = sim.mutate_add_link(g);
        g = sim.mutate_add_link(g);
        // fmt::print("PRE unit\n{}\n", g.format());
        const auto b = sim.create_brain(g);
        Unit u{g, b};
        units.push_back(u);
        // fmt::print("POST unit\n{}\n", units.back().genome.format());
    }

    // for (auto& u : units)
    //    {
    //        fmt::print("INITIAL unit\n{}\n", units.back().genome.format());
    //    }
    // return 0;
    for(int epoch = 0; epoch < epochs; epoch++) {
        // eval
        for(auto& u : units) {
            for(int t = 0; t < tests; t++) {
                int i1 = Random::get<int>(0, 1);
                int i2 = Random::get<int>(0, 1);
                float out = (i1 == i2) ? -1 : 1;
                auto out2 = u.brain.eval({i1, i2})[0];
                if(out2 < 0)
                    out2 = 0;
                else if(out2 > 0)
                    out2 = 1;
                if((i1 ^ i2) == out2)
                    u.score++;
                else
                    u.score--;
                // u.score += (out - out2) * (out - out2);
                // fmt::print("t {}{} = {:<4} -- {}\n", i1, i2, out, out2);
            }
            // fmt::print("\n");
        }

        // sort scores
        std::partial_sort(begin(units), begin(units) + top, end(units),
                          [](const auto& l, const auto& r) { return l.score > r.score; });

        // fmt::print("\nSCORE -- {}\n", epoch);
        // for(const auto& u : units) {
        //    fmt::print("  s={:<10}\n", u.score);
        //}
        fmt::print("epoch {:<4} top= {:<20}", epoch, units.front().score);
        for(int i = 0; i <= units.front().score; i++)
            fmt::print("*");
        fmt::print("\n");

        // remove bottom scorers
        units.erase(begin(units) + top, end(units));
        assert(units.size() > 0);

        // add offsprings
        for(int i = 0; i < top; ++i) {
            // fmt::print("PARENT\n{}\n", units[i].genome.format());
            const auto& g = units[i].genome;
            // mutate offspring
            // Genome new_g =
            // sim.mutate_add_link(units[i].genome);
            auto r = Random::get(0.0f, 1.0f);

            if(r < 0.8) {
                // fmt::print("RANDOM weight\n");
                Genome new_g = sim.mutate_weight(g);
                units.push_back(Unit{new_g, sim.create_brain(new_g)});
            } else {
                if(Random::get(0.f, 1.f) < 0.5) {
                    // fmt::print("RANDOM link\n");
                    Genome new_g = sim.mutate_add_link(g);
                    units.push_back(Unit{new_g, sim.create_brain(new_g)});
                } else {
                     //fmt::print("RANDOM node\n");
                    Genome new_g = sim.mutate_add_node(g);
                    units.push_back(Unit{new_g, sim.create_brain(new_g)});
                }
            }

            //[&g,             //    if(r < 0.333333)
            //        return sim.mutate_weight(g);
            //    else
            //    if(r < 0.666666)
            //        return sim.mutate_add_link(g);
            //    else
            //        return sim.mutate_add_node(g);
            //}();
            // units.push_back(Unit{new_g, sim.create_brain(new_g)});
            // fmt::print("CHILD\n{}\n\n", units[i].genome.format());
            // assert(units[i].genome.format() == units.back().genome.format());
            // fmt::print("new unit\n{}\n", units.back().genome.format());

            // zero score
            units[i].score = 0;
            units[i].brain.reset_values();
        }
        // for (auto& u : units)
        //{
        //    fmt::print("new unit\n{}\n", units.back().genome.format());
        //}
        assert(size(units) == pops);

        //
    }

    units.erase(begin(units) + top, end(units));
    // test final
    for(auto& u : units) {
        for(int t = 0; t < tests; t++) {
            int i1 = Random::get<int>(0, 1);
            int i2 = Random::get<int>(0, 1);
            float out = (i1 == i2) ? -1 : 1;
            auto out2 = u.brain.eval({i1, i2})[0];
            u.score += (out - out2) * (out - out2);
            // fmt::print("t {}{} = {:<4} -- {}\n", i1, i2, out, out2);
        }
        // fmt::print("\n");
    }
    fmt::print("\nTEST\n");
    for(const auto& u : units) {
        // fmt::print("{}\n", u.genome.format());
        fmt::print("{}\n", u.brain.format());
        {
            auto b = u.brain;
            auto o = b.eval({0, 0})[0];
            fmt::print("0 xor 0 = {}\n", o);
        }
        {
            auto b = u.brain;
            auto o = b.eval({1, 1})[0];
            fmt::print("1 xor 1 = {}\n", o);
        }
        {
            auto b = u.brain;
            auto o = b.eval({0, 1})[0];
            fmt::print("0 xor 1 = {}\n", o);
        }
        {
            auto b = u.brain;
            auto o = b.eval({1, 0})[0];
            fmt::print("1 xor 0 = {}\n", o);
        }
        fmt::print("\n");
    }
    // auto g = sim.create_genome();
    // for(int i = 0; i < 100; ++i) {
    //    constexpr auto m = std::array{1, 2, 3};
    //    switch(*Random::get(m)) {
    //        case 1:
    //            g = sim.mutate_add_link(g);
    //            break;
    //        case 2:
    //            g = sim.mutate_add_node(g);
    //            break;
    //        case 3:
    //            g = sim.mutate_weight(g);
    //            break;
    //        default:
    //            assert(false);
    //    }
    //}
    // auto b = sim.create_brain(g);
    // fmt::print("{}\n", b.format());
    // for(int i = 0; i < 100; ++i) {
    //    auto output = b.eval({1, 1});
    //    fmt::print("{}\n", b.format());
    //    fmt::print("\n---- output {} ----\n", i);
    //    for(auto o : output) {
    //        fmt::print("  -- {}\n", o);
    //    }
    //}
    // g = sim.test_add_link(g, 2, 5);
    // fmt::print("{}\n", g.format());
    // g = sim.test_add_node(g, 2, 5);
    // fmt::print("{}\n", g.format());
    // g = sim.test_add_link(g, 3, 5);
    // fmt::print("{}\n", g.format());
    // auto i = g.add_hidden_node();
    // fmt::print("   hidden {}\n", i);

    // g.add_connection(2, {1, 3}, 1, false);
    // g.add_connection(2, {1, 2}, 1, false);
    // g.add_connection(2, {1, 1}, 1, false);
    // fmt::print("{}\n", g.format());

    // constexpr auto get_add = [] (neat::Genome& g) {
    //    return [&g] (neat::NodeIndex in, neat::NodeIndex out) {
    //        mutate_add_link(g, {in, out}, 1);
    //    };
    //};
    // constexpr auto get_split = [] (neat::Genome& g) {
    //    return [&g] (neat::NodeIndex in, neat::NodeIndex out) {
    //        mutate_split_link(g, {in, out});
    //    };
    //};
    //    auto g1 = neat::create_genome(2, 1);
    //    {
    //        auto add = get_add(g1);
    //        auto split = get_split(g1);
    //        add(1, 3);
    //        split(1, 3);
    //        add(2, 4);
    //        split(2, 4);
    //        add(2, 3);
    //        split(2, 3);
    //        fmt::print(format_nodes(g1));
    //        fmt::print(format_links(g1));
    //    }
    //    fmt::print("\n");
    //    auto g2 = neat::create_genome(2, 1);
    //    {
    //        auto add = get_add(g2);
    //        auto split = get_split(g2);
    //        add(1, 3);
    //        add(2, 3);
    //        split(1, 3);
    //        split(2, 3);
    //        fmt::print(format_nodes(g2));
    //        fmt::print(format_links(g2));
    //        auto net = neat::create_neural_network(g2);
    //    }
    // auto g3 = neat::create_genome(3, 2);
    //{
    //    auto add = get_add(g3);
    //    auto split = get_split(g3);
    //    add(1, 4);
    //    add(2, 4);
    //    add(3, 5);
    //    split(1, 4);
    //    split(2, 4);
    //    add(6, 7);
    //    split(3, 5);
    //    add(7, 8);
    //    add(7, 5);
    //    split(7, 5);
    //    add(8, 9);
    //    fmt::print(format_nodes(g3));
    //    fmt::print(format_links(g3));
    //    auto net = neat::create_brain(g3);
    //    fmt::print("\n{}", format(net));
    //    auto output = eval(net, {1, 2, 3});
    //}
    // auto g4 = neat::create_genome(2, 1);
    //{
    //    auto add = get_add(g4);
    //    auto split = get_split(g4);
    //    add(2, 3);
    //    mutate_add_memory(g4, {2, 3});
    //    split(2, 3);
    //    add(1, 5);
    //    add(5, 4);
    //    add(3, 4);
    //    fmt::print(format_nodes(g4));
    //    fmt::print(format_links(g4));
    //    auto net = neat::create_brain(g4);
    //    fmt::print("\n{}", format(net));
    //    auto output = eval(net, {1, 2});
    //    output = eval(net, {1, 2});
    //}
    // auto g5 = neat::create_genome(3, 2);
    //{
    //    auto add = get_add(g5);
    //    auto split = get_split(g5);
    //    add(1, 4);
    //    add(2, 4);clTabCtrl
    //    add(3, 5);
    //    split(1, 4);
    //    split(2, 4);
    //    add(6, 7);
    //    split(3, 5);clTabCtrl
    //    add(7, 8);
    //    add(7, 5);
    //    split(7, 5);
    //    add(8, 9);
    //    fmt::print(format_nodes(g5));
    //    fmt::print(format_links(g5));
    //    auto links = get_available_links(g5);
    //    fmt::print("---- available links ----\n");
    //    for (auto edge : links) {
    //        fmt::print("  {} -> {}\n", edge.in, edge.out);
    //    }
    //}

    return 0;
}
