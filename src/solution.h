#ifndef _SOLUTION_H
#define _SOLUTION_H


#include <stdlib.h>

#include "instance.h"


// Penalty for k0 different than k.
#define P1 1e9


typedef struct
{
    Instance *instance;

    // `next[i]`: node that node `i` is connected to.
    size_t *next;

    // `route[j]`: first node in the `j`-th route (it's also one of the `k0`
    // nodes that the depot connects).
    size_t *route;

    // Number of routes in the solution.
    size_t k0;
} Solution;

Solution *load_solution(Instance *instance);

void free_solution(Solution *solution);

// Set a configuration like this:
// r0: 0 -> 1 -> 2 -> ... -> n-1 -> 0
void set_arbitrary_configuration(Solution *solution);

#endif // _SOLUTION_H
