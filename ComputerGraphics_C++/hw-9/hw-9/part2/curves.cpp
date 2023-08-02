#include "common.h"

// Evaluate curve c at t and return the result.  If sub_a or sub_b are not null,
// perform subdivision on curve c at t as well.  If sub_a is not null, assign it
// the first piece (so that sub_a and c agree at their endpoint A.)  If sub_b is
// not null, assign it the second piece (so that sub_b and c agree at their
// endpoint D.)
vec2 Evaluate(const Curve& c, double t, Curve* sub_a, Curve* sub_b)
{
    return {};
}

