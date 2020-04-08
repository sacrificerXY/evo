#include "Link.h"

bool operator==(Link l, Link r)
{
    return l.from == r.from && l.to == r.to;
}

bool operator!=(Link l, Link r)
{
    return !(l == r);
}
