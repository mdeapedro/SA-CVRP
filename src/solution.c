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
