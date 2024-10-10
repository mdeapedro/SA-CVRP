#ifndef _SOLUTION_H
#define _SOLUTION_H


#include <stdlib.h>

#include "instance.h"


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

#endif // _SOLUTION_H
