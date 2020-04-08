#include "neat/mutator.h"

#include <fmt/core.h>


namespace neat
{
    

//Genome Mutator::add_connection(const Genome& g, NodeIndex from, NodeIndex to)
//{
//    fmt::print("Mutator::add_connection({}, {})\n", from, to);
//    return neat::add_connection(g, from, to, -111);
//}
//    
//Genome Mutator::add_node(const Genome& g, NodeIndex from, NodeIndex to)
//{
//    auto new_g = neat::add_hidden_node(g);
//    const auto index = g.num_inputs + g.num_outputs + g.num_hidden;
//    new_g = neat::add_connection(new_g, Node::BIAS_INDEX, index, 50);
//    new_g = neat::add_connection(new_g, from, index, -5);
//    new_g = neat::add_connection(new_g, index, to, 5);
//    return new_g;
//}
//    
    
    
}