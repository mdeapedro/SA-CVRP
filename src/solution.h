#ifndef _SOLUTION_H
#define _SOLUTION_H


#include <stdlib.h>

#include "instance.h"


// Penalty for route exceeding vehicle capacity.
#define P1 1e9

typedef size_t Node;


typedef struct
{
    Instance *instance;

    // `routes[i][j]`: `node[j]` of `routes[i]`
    Node **routes;

    // `k0[i]`: Number of nodes in `routes[i]`.
    size_t *k0;
} Solution;

Solution *load_solution(Instance *instance);

void free_solution(Solution *solution);

void set_configuration(Solution *solution, Node **routes, size_t *k0);

// Set a configuration like this:
// r1: 0 -> 1 -> 2 -> ... -> n/k -> 0
// r2: 0 -> n/k+1 -> ... -> 2n/k -> 0
// ...
// rk: 0 -> n-n/k+1 -> ... -> n -> 0
void set_arbitrary_configuration(Solution *solution);

double calculate_cost(Solution *solution);

// Insert `node` in route `i` at position `j`
void insert_node(Solution *solution, Node node, size_t i, size_t j);

// Delete node in route `i` at position `j`.
void delete_node(Solution *solution, size_t i, size_t j);


#endif // _SOLUTION_H
