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

void split(Solution *solution, Node node_a, Node node_b)
{
    if (
        node_a == 0 ||
        node_b == 0 ||
        node_a == node_b ||
        solution->next[node_a] == node_b
    ) return;

    solution->prev[solution->next[node_a]] = 0;
    solution->route[solution->k0++] = solution->next[node_a];
    solution->next[node_a] = node_b;
    solution->next[solution->prev[node_b]] = 0;
    solution->prev[node_b] = node_a;
}
