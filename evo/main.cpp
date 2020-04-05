
#include <fmt/core.h>

#include "neat/neat.h"



int main()
{
    constexpr auto get_add = [] (neat::Genome& g) {
        return [&g] (neat::NodeIndex in, neat::NodeIndex out) {
            mutate_add_link(g, {in, out}, 1);
        };
    };
    constexpr auto get_split = [] (neat::Genome& g) {
        return [&g] (neat::NodeIndex in, neat::NodeIndex out) {
            mutate_split_link(g, {in, out});
        };
    };
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
    //auto g3 = neat::create_genome(3, 2);
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
    auto g4 = neat::create_genome(2, 1);
    {
        auto add = get_add(g4);
        auto split = get_split(g4);
        add(2, 3);
        mutate_add_memory(g4, {2, 3});
        split(2, 3);
        add(1, 5);
        add(5, 4);
        add(3, 4);
        fmt::print(format_nodes(g4));
        fmt::print(format_links(g4));
        auto net = neat::create_brain(g4);
        fmt::print("\n{}", format(net));
        auto output = eval(net, {1, 2});
        output = eval(net, {1, 2});
    }
	return 0;
}
