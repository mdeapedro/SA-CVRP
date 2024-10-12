#include "solution.h"


Solution *load_solution(Instance *instance)
{
    Solution *solution = malloc(sizeof(Solution));
    solution->next = malloc(instance->n * sizeof(Node));
    solution->prev = malloc(instance->n * sizeof(Node));
    solution->route = malloc(instance->n * sizeof(Node));

    solution->instance = instance;
    solution->k0 = 0;

    return solution;
}

void free_solution(Solution *solution)
{
    free(solution->route);
    free(solution->prev);
    free(solution->next);
    free(solution);
}

void set_arbitrary_configuration(Solution *solution)
{
    for (Node i = 1; i < solution->instance->n; ++i)
    {
        solution->next[i] = i + 1;
        solution->prev[i] = i - 1;
    }
    solution->next[solution->instance->n - 1] = 0;
    solution->route[0] = 1;
    solution->k0 = 1;
}

double calculate_cost(Solution *solution)
{
    double cost = 0.0;

    for (size_t j = 0; j < solution->k0; ++j)
    {
        int current_capacity = solution->instance->q;

        Node node = solution->route[j];

        cost += solution->instance->cost[0][node];
        while (node != 0)
        {
            cost += solution->instance->cost[node][solution->next[node]];
            current_capacity -= solution->instance->demand[node];
            node = solution->next[node];
        }

        cost += P2 * (current_capacity < 0);
    }

    cost += P1 * abs((int)solution->instance->k - (int)solution->k0);

    return cost;
}

void split(Solution *solution, Node node)
{
    if (
        node == 0 ||
        solution->next[node] == 0
    ) return;

    solution->prev[solution->next[node]] = 0;
    solution->route[solution->k0++] = solution->next[node];
    solution->next[node] = 0;
}

// Runs in O(n).
// May be improved by using memoization.
Node _get_route_tail(Solution *solution, size_t route_j)
{
    Node node = solution->route[route_j];
    while (solution->next[node] != 0)
    {
        node = solution->next[node];
    }

    return node;
}

void _delete_route(Solution *solution, size_t route_j)
{
    solution->route[route_j] = solution->route[--solution->k0];
}

void join(Solution *solution, size_t route_a, size_t route_b)
{
    if (
        route_a == route_b ||
        route_a >= solution->k0 ||
        route_b >= solution->k0
    ) return;

    Node node_a = _get_route_tail(solution, route_a);
    Node node_b = solution->route[route_b];

    solution->next[node_a] = node_b;
    solution->prev[node_b] = node_a;

    _delete_route(solution, route_b);
}

// Time complexity may be improved.
// It's guaranteed that `node` is the beginning of a route.
size_t _find_node_route(Solution *solution, Node node)
{
    size_t j = 0;
    for (; j < solution->k0 && solution->route[j] != node; ++j);

    return j;
}

void steal(Solution *solution, Node node_a, Node node_b)
{
    if (
        node_a == 0 ||
        node_b == 0
    ) return;

    if (
        solution->prev[node_b] == 0 &&
        solution->next[node_b] == 0
    ) _delete_route(solution, _find_node_route(solution, node_b));

    solution->next[solution->prev[node_b]] = solution->next[node_b];
    solution->prev[solution->next[node_b]] = solution->prev[node_b];

    solution->next[node_b] = solution->next[node_a];
    solution->prev[solution->next[node_a]] = node_b;

    solution->next[node_a] = node_b;
    solution->prev[node_b] = node_a;
}
