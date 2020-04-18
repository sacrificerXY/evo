#pragma once

#include <vector>

struct GenomeLink {
    int id;
    int from;
    int to;
    float weight;
    bool enabled;
};
bool operator==(const GenomeLink& l, const GenomeLink& r);
bool operator<(const GenomeLink& l, const GenomeLink& r);
bool operator<(const GenomeLink& l, int id);


void 
add_link(std::vector<GenomeLink>& links, const GenomeLink& link);

void 
disable_link(std::vector<GenomeLink>& links, int id);

GenomeLink 
get_link(const std::vector<GenomeLink>& links, int id);

bool 
has_link(const std::vector<GenomeLink>& links, int id);