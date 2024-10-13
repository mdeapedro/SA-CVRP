#include <string.h>

#include "solution.h"
#include "stdio.h"


Solution *load_solution(Instance *instance)
{
    Solution *solution = malloc(sizeof(Solution));

    solution->routes = malloc(instance->k * sizeof(Node *));
    for (size_t i = 0; i < instance->k; ++i)
    {
        solution->routes[i] = malloc(instance->n * sizeof(Node));
    }

    solution->k0 = malloc(instance->k * sizeof(size_t));

    solution->instance = instance;

    return solution;
}

void free_solution(Solution *solution)
{
    free(solution->k0);
    for (size_t i = 0; i < solution->instance->k; ++i)
    {
        free(solution->routes[i]);
    }
    free(solution->routes);
    free(solution);
}

void set_configuration(Solution *solution, Node **routes, size_t *k0)
{
    for (size_t i = 0; i < solution->instance->k; ++i)
    {
        memcpy(solution->routes[i], routes[i], k0[i] * sizeof(Node));
    }
    memcpy(solution->k0, k0, solution->instance->k * sizeof(size_t));
}

void set_arbitrary_configuration(Solution *solution)
{
    size_t nodes_per_route = (solution->instance->n - 1) / solution->instance->k;
    for (size_t i = 0; i < solution->instance->k; ++i)
    {
        for (Node j = 0; j < nodes_per_route; ++j)
        {
            solution->routes[i][j] = j + i * nodes_per_route + 1;
        }
        solution->k0[i] = nodes_per_route;
    }
    size_t nodes_remaining = solution->instance->n - 1 - (nodes_per_route * solution->instance->k);
    for (Node j = 0; j < nodes_remaining; j++)
    {
        solution->routes[solution->instance->k - 1][nodes_per_route + j] = solution->instance->n - nodes_remaining + j;
        ++solution->k0[solution->instance->k - 1];
    }
}

double calculate_cost(Solution *solution)
{
    double cost = 0.0;

    for (size_t i = 0; i < solution->instance->k; ++i)
    {
        int current_capacity = solution->instance->q;

        cost += solution->instance->cost[0][solution->routes[i][0]];
        for (size_t j = 0; j < solution->k0[i] - 1; ++j)
        {
            cost += solution->instance->cost[solution->routes[i][j]][solution->routes[i][j + 1]];
            current_capacity -= solution->instance->demand[solution->routes[i][j]];
        }
        cost += solution->instance->cost[solution->routes[i][solution->k0[i] - 1]][0];
        current_capacity -= solution->instance->demand[solution->routes[i][solution->k0[i] - 1]];

        cost += P1 * (current_capacity < 0);
    }

    return cost;
}

void insert_node(Solution *solution, Node node, size_t i, size_t j)
{
    for (size_t l = solution->k0[i]; l > j; --l)
    {
        solution->routes[i][l] = solution->routes[i][l - 1];
    }
    ++solution->k0[i];

    solution->routes[i][j] = node;
}

void delete_node(Solution *solution, size_t i, size_t j)
{
    --solution->k0[i];
    for (size_t l = j; l < solution->k0[i]; ++l)
    {
        solution->routes[i][l] = solution->routes[i][l + 1];
    }
}
