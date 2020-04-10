
#include <algorithm>
#include <array>
#include <cassert>
#include <vector>

#include <fmt/core.h>


#include <effolkronium/random.hpp>
// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

#ifndef DOCTEST_CONFIG_DISABLE
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS // defined so the asserts are crazy fast - both for compilation and execution
#endif

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

//#include "Simulation.h"
//struct Unit {
//    Genome genome;
//    Brain brain;
//    float score = 0.f;
//};

#include "neat_types.h"

int prog_main()
{
    create_genome(1, 1);
    //constexpr int epochs = 1000;
    //constexpr int pops = 200;
    //constexpr int top = pops / 2;
    //constexpr int rand_pops = 0.f;
    //constexpr int tests = 10;
    //Simulation sim(2, 1);

    //auto units = std::vector<Unit>();
    //for(int i = 0; i < pops + rand_pops; i++) {
    //    auto g = sim.create_genome();
    //    g = sim.mutate_add_link(g);
    //    g = sim.mutate_add_link(g);
    //    g = sim.mutate_add_link(g);
    //    g = sim.mutate_add_link(g);
    //    g = sim.mutate_add_link(g);
    //    g = sim.mutate_add_link(g);
    //    // fmt::print("PRE unit\n{}\n", g.format());
    //    const auto b = sim.create_brain(g);
    //    Unit u{g, b};
    //    units.push_back(u);
    //    // fmt::print("POST unit\n{}\n", units.back().genome.format());
    //}

    //// for (auto& u : units)
    ////    {
    ////        fmt::print("INITIAL unit\n{}\n", units.back().genome.format());
    ////    }
    //// return 0;
    //for(int epoch = 0; epoch < epochs; epoch++) {
    //    // eval
    //    for(auto& u : units) {
    //        for(int t = 0; t < tests; t++) {
    //            int i1 = Random::get<int>(0, 1);
    //            int i2 = Random::get<int>(0, 1);
    //            float out = (i1 == i2) ? -1 : 1;
    //            auto out2 = u.brain.eval({i1, i2})[0];
    //            if(out2 < 0)
    //                out2 = 0;
    //            else if(out2 > 0)
    //                out2 = 1;
    //            if((i1 ^ i2) == out2)
    //                u.score++;
    //            else
    //                u.score--;
    //            // u.score += (out - out2) * (out - out2);
    //            // fmt::print("t {}{} = {:<4} -- {}\n", i1, i2, out, out2);
    //        }
    //        // fmt::print("\n");
    //    }

    //    // sort scores
    //    std::partial_sort(begin(units), begin(units) + top, end(units),
    //                      [](const auto& l, const auto& r) { return l.score > r.score; });

    //    // fmt::print("\nSCORE -- {}\n", epoch);
    //    // for(const auto& u : units) {
    //    //    fmt::print("  s={:<10}\n", u.score);
    //    //}
    //    fmt::print("epoch {:<4} top= {:<20}", epoch, units.front().score);
    //    for(int i = 0; i <= units.front().score; i++)
    //        fmt::print("*");
    //    fmt::print("\n");

    //    // remove bottom scorers
    //    units.erase(begin(units) + top, end(units));
    //    assert(units.size() > 0);

    //    // add offsprings
    //    for(int i = 0; i < top; ++i) {
    //        // fmt::print("PARENT\n{}\n", units[i].genome.format());
    //        const auto& g = units[i].genome;
    //        // mutate offspring
    //        // Genome new_g =
    //        // sim.mutate_add_link(units[i].genome);
    //        auto r = Random::get(0.0f, 1.0f);

    //        if(r < 0.8) {
    //            // fmt::print("RANDOM weight\n");
    //            Genome new_g = sim.mutate_weight(g);
    //            units.push_back(Unit{new_g, sim.create_brain(new_g)});
    //        } else {
    //            if(Random::get(0.f, 1.f) < 0.5) {
    //                // fmt::print("RANDOM link\n");
    //                Genome new_g = sim.mutate_add_link(g);
    //                units.push_back(Unit{new_g, sim.create_brain(new_g)});
    //            } else {
    //                // fmt::print("RANDOM node\n");
    //                Genome new_g = sim.mutate_add_node(g);
    //                units.push_back(Unit{new_g, sim.create_brain(new_g)});
    //            }
    //        }

    //        //[&g,             //    if(r < 0.333333)
    //        //        return sim.mutate_weight(g);
    //        //    else
    //        //    if(r < 0.666666)
    //        //        return sim.mutate_add_link(g);
    //        //    else
    //        //        return sim.mutate_add_node(g);
    //        //}();
    //        // units.push_back(Unit{new_g, sim.create_brain(new_g)});
    //        // fmt::print("CHILD\n{}\n\n", units[i].genome.format());
    //        // assert(units[i].genome.format() == units.back().genome.format());
    //        // fmt::print("new unit\n{}\n", units.back().genome.format());

    //        // zero score
    //        units[i].score = 0;
    //        units[i].brain.reset_values();
    //    }
    //    // for (auto& u : units)
    //    //{
    //    //    fmt::print("new unit\n{}\n", units.back().genome.format());
    //    //}
    //    assert(size(units) == pops);

    //    //
    //}

    //units.erase(begin(units) + top, end(units));
    //// test final
    //for(auto& u : units) {
    //    for(int t = 0; t < tests; t++) {
    //        int i1 = Random::get<int>(0, 1);
    //        int i2 = Random::get<int>(0, 1);
    //        float out = (i1 == i2) ? -1 : 1;
    //        auto out2 = u.brain.eval({i1, i2})[0];
    //        u.score += (out - out2) * (out - out2);
    //        // fmt::print("t {}{} = {:<4} -- {}\n", i1, i2, out, out2);
    //    }
    //    // fmt::print("\n");
    //}
    //fmt::print("\nTEST\n");
    //for(const auto& u : units) {
    //    // fmt::print("{}\n", u.genome.format());
    //    fmt::print("{}\n", u.brain.format());
    //    {
    //        auto b = u.brain;
    //        auto o = b.eval({0, 0})[0];
    //        fmt::print("0 xor 0 = {}\n", o);
    //    }
    //    {
    //        auto b = u.brain;
    //        auto o = b.eval({1, 1})[0];
    //        fmt::print("1 xor 1 = {}\n", o);
    //    }
    //    {
    //        auto b = u.brain;
    //        auto o = b.eval({0, 1})[0];
    //        fmt::print("0 xor 1 = {}\n", o);
    //    }
    //    {
    //        auto b = u.brain;
    //        auto o = b.eval({1, 0})[0];
    //        fmt::print("1 xor 0 = {}\n", o);
    //    }
    //    fmt::print("\n");
    //}

    return 0;
}

static void handler(const doctest::AssertData& ad) {
    using namespace doctest;

    // uncomment if asserts will be used in a multi-threaded context
    // std::lock_guard<std::mutex> lock(g_mut);

    // here we can choose what to do:
    // - log the failed assert
    // - throw an exception
    // - call std::abort() or std::terminate()

    std::cout << Color::LightGrey << skipPathFromFilename(ad.m_file) << "(" << ad.m_line << "): ";
    std::cout << Color::Red << failureString(ad.m_at) << ": ";

    // handling only normal (comparison and unary) asserts - exceptions-related asserts have been skipped
    if(ad.m_at & assertType::is_normal) {
        std::cout << Color::Cyan << assertString(ad.m_at) << "( " << ad.m_expr << " ) ";
        std::cout << Color::None << (ad.m_threw ? "THREW exception: " : "is NOT correct!\n");
        if(ad.m_threw)
            std::cout << ad.m_exception;
        else
            std::cout << "  values: " << assertString(ad.m_at) << "( " << ad.m_decomp << " )";
    } else {
        std::cout << Color::None << "an assert dealing with exceptions has failed!";
    }

    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    doctest::Context context;

    // !!! THIS IS JUST AN EXAMPLE SHOWING HOW DEFAULTS/OVERRIDES ARE SET !!!

    // defaults
    context.addFilter("test-case-exclude", "*math*");  // exclude test cases with "math" in their name
    context.setOption("abort-after", 5);               // stop test execution after 5 failed assertions
    context.setOption("order-by", "name");             // sort the test cases by their name

    context.applyCommandLine(argc, argv);

    // overrides
    context.setOption("no-breaks", true);  // don't break in the debugger when assertions fail

    int res = context.run();  // run

    if(context.shouldExit())  // important - query flags (and --exit) rely on the user doing this
        return res;           // propagate the result of the tests
    context.setAsDefaultForAssertsOutOfTestCases();
    context.setAssertHandler(handler);
    int client_stuff_return_code = prog_main();
    fmt::print("qweqwe]");

    // your program - if the testing framework is integrated in your production code

    return res + client_stuff_return_code;  // the result from doctest is propagated here as well
}
