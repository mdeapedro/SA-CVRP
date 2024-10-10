#include "solution.h"


Solution *load_solution(Instance *instance)
{
    Solution *solution = malloc(sizeof(Solution));
    solution->next = malloc(instance->n * sizeof(size_t));
    solution->route = malloc(instance->n * sizeof(size_t));

    solution->instance = instance;
    solution->k0 = 0;

    return solution;
}

void free_solution(Solution *solution)
{
    free(solution->route);
    free(solution->next);
    free(solution);
}

void set_arbitrary_configuration(Solution *solution)
{
    for (size_t i = 1; i < solution->instance->n; ++i)
    {
        solution->next[i] = i + 1;
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
        size_t node = solution->route[j];
        cost += solution->instance->cost[0][node];
        while (node != 0)
        {
            cost += solution->instance->cost[node][solution->next[node]];
            node = solution->next[node];
        }
    }

    cost += P1 * abs((int)solution->instance->k - (int)solution->k0);

    return cost;
}
