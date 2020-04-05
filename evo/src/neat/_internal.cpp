#include "neat/_internal.h"

#include <algorithm>
#include <cassert>
#include <map>


#include <fmt/core.h>


namespace neat
{
    bool operator<(Edge edge1, Edge edge2)
    {
        if (edge1.in < edge2.in) {
            return true;
        }
        if (edge1.in == edge2.in and edge1.out < edge2.out) {
            return true;
        }
        return false;
    }

    bool operator==(Edge edge1, Edge edge2)
    {
        return edge1.in == edge2.in && edge1.out == edge2.out;
    }
}

namespace neat::internal
{
    std::map<Edge, LinkId> edges;
    LinkId id_count = 0;

    LinkId get_id(Edge edge)
    {
        if (!edges.contains(edge)) {
            edges[edge] = id_count++;
        }
        return edges[edge];
    }

    void add_link(LinkIds& linkIds, Links& links, Edge edge, float weight)
    {
        assert(edge.in != edge.out);
        assert(not contains(links, edge));
        //assert(not contains(links, {edge.out, edge.in}));
        fmt::print("add link ({} -> {}) w={}\n", edge.in, edge.out, weight);

        auto id_begin = cbegin(linkIds);
        auto id_end = cend(linkIds);
        auto id = get_id(edge);
        auto insert_index = std::distance(
            id_begin,
            std::lower_bound(id_begin, id_end, id)
        );
        linkIds.emplace(next(id_begin, insert_index), id);
        links.emplace(
            next(begin(links), insert_index),
            Link{edge, weight, true}
        );
    }

    bool contains(const Links& links, Edge edge)
    {
        return std::find_if(cbegin(links), cend(links), [edge] (const Link& link) {
            return link.edge == edge;
        }) != cend(links);
    }
}
