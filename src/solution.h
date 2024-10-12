#ifndef _SOLUTION_H
#define _SOLUTION_H


#include <stdlib.h>

#include "instance.h"


// Penalty for k0 different than k.
#define P1 1e9

// Penalty for route exceeding vehicle capacity.
#define P2 1e9

typedef size_t Node;


typedef struct
{
    Instance *instance;

    // `next[i]`: node that node `i` is connected to.
    Node *next;

    // `prev[i]`: node that connects node `i`.
    Node *prev;

    // `route[j]`: first node in the `j`-th route (it's also one of the `k0`
    // nodes that the depot connects).
    Node *route;

    // Number of routes in the solution.
    size_t k0;
} Solution;

Solution *load_solution(Instance *instance);

void free_solution(Solution *solution);

// Set a configuration like this:
// r0: 0 -> 1 -> 2 -> ... -> n-1 -> 0
void set_arbitrary_configuration(Solution *solution);

double calculate_cost(Solution *solution);

// Split `node`-`next[node]` route.
// It does nothing if:
// 1. `node` == 0 or
// 2. `next[node]` == 0.
int split(Solution *solution, Node node);

// It does nothing if:
// 1. `route_a` == `route_b`
// 2. `route_a`, `route_b` >= `k0`
int merge(Solution *solution, size_t route_a, size_t route_b);

// Connect `node_a` to `node_b`.
// It does nothing if:
// 1. `node_a` == 0 or
// 2. `node_b` == 0.
int steal(Solution *solution, Node node_a, Node node_b);


#endif // _SOLUTION_H
