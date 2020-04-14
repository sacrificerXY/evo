#pragma once

#include <numeric>
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
    
    // do depth first search starting from output node
    // all nodes visited by dfs is then considered useful
    std::set<int> useful_nodes;
    {
        // add output indices at the start
        std::vector<int> stack(num_outputs);
        std::iota(stack.begin(), stack.end(), num_inputs); // generates [num_inputs to num_inputs+num_outputs]
  
      
        while (!stack.empty()) {
            auto curr = stack.back();
            stack.pop_back();
            useful_nodes.insert(curr);
            
            const auto& next_nodes = reverse_adjacency_list[curr];
            for (auto n : next_nodes) {
                if (useful_nodes.contains(n)) continue;
                if (std::find(stack.begin(), stack.end(), n) != stack.end()) continue;
                //fmt::print("    add to stack {}\n", n);
                stack.push_back(n);
            }
        }
    }
    
    // sometimes not all input indices are connected to output
    // still, make sure to add input indices no matter what
    for (int i = 0; i < num_inputs + num_outputs; ++i) {
        useful_nodes.insert(i);
    }
    
    return useful_nodes;
}