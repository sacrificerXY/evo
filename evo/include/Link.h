#pragma once

#include <set>
#include <vector>

template <typename L>
concept cLink = requires(L l) {
    { l.from } -> int;
    { l.to } -> int;
};

auto get_useful_nodes(int num_inputs, int num_outputs, const std::vector<cLink>& links)
{
    std::unordered_map<int, std::vector<int>> reverse_adjacency_list;
    for (const auto& l : links) {
        reverse_adjacency_list[l.to].push_back(l.from);
    }
    
    std::set<int> useful_nodes;
    {
        std::vector<int> stack;
        for (int i = num_inputs; i < num_inputs + num_outputs; ++i) {
            stack.push_back(i);
        }
        
        while (!stack.empty()) {
            auto curr = stack.back();
            stack.pop_back();
            //fmt::print("checking... {}\n", curr);
            //fmt::print("in  = {{{}}}\n", fmt::join(useful_nodes, ", "));
            //fmt::print("stk = {{{}}}\n", fmt::join(stack, ", "));
            //fmt::print("    add to in {}\n", curr);
            useful_nodes.insert(curr);
            for (auto n : reverse_adjacency_list[curr]) {
                if (useful_nodes.contains(n)) continue;
                if (std::find(stack.begin(), stack.end(), n) != stack.end()) continue;
                //fmt::print("    add to stack {}\n", n);
                stack.push_back(n);
            }
        }
    }
    
    // make sure to add input and output nodes no matter what
    for (int i = 0; i < num_inputs + num_outputs; ++i) {
        useful_nodes.insert(i);
    }
    
    return useful_nodes;
}