#include <time.h>
#include <math.h>

#include "sa.h"
#include "utils.h"


static double _compute_K(Instance *instance)
{
    double K = 0.0;
    for (size_t i = 0; i < instance->n; ++i)
    {
        for (size_t j = 0; j < instance->n; j++)
        {
            K += instance->cost[i][j];
        }
    }

    K /= instance->n;

    K = 1/K;

    return K;
}

Solution *sa_solve(const InputParameters ip, const OutputParameters op, const SA_Parameters sap)
{
    srand(ip.seed);

    Solution *solution = load_solution(ip.instance);
    set_arbitrary_configuration(solution);

    FILE *output = op.output;

    double temperature = sap.initial_temperature;
    const double alpha = sap.alpha;
    const double K = _compute_K(solution->instance);

    double best_cost_found = 1e18;
    Solution *best_solution_found = load_solution(ip.instance);

    const clock_t initial_clock = clock();
    const clock_t stop_clock = initial_clock + ip.time_limit_seconds * CLOCKS_PER_SEC;
    while (1)
    {
        clock_t current_clock = clock();

        if (!(current_clock < stop_clock)) break;

        double delta_cost = calculate_cost(solution);

        if (delta_cost < best_cost_found)
        {
            unsigned long current_time_seconds = (current_clock - initial_clock) / CLOCKS_PER_SEC;
            fprintf(output, "%ld: New best cost found: %f\n", current_time_seconds, delta_cost);
            best_cost_found = delta_cost;
            set_configuration(best_solution_found, solution->routes, solution->k0);
        }

        size_t random_i_1 = random_ab(0, solution->instance->k);
        size_t random_i_2 = random_ab(0, solution->instance->k);

        size_t random_j_1 = random_ab(0, solution->k0[random_i_1]);
        size_t random_j_2 = random_ab(0, solution->k0[random_i_2]);

        while (solution->k0[random_i_1] == 1) random_i_1 = random_ab(0, solution->instance->k);

        Node node = solution->routes[random_i_1][random_j_1];

        delete_node(solution, random_i_1, random_j_1);
        insert_node(solution, node, random_i_2, random_j_2);

        delta_cost = calculate_cost(solution) - delta_cost;

        if (delta_cost > 0 && random_01() > exp(-K * delta_cost / temperature))
        {
            delete_node(solution, random_i_2, random_j_2);
            insert_node(solution, node, random_i_1, random_j_1);
        }

        temperature = fmax(1e-300, temperature * alpha);
    }

    double cost = calculate_cost(solution);
    if (cost < best_cost_found)
    {
        best_cost_found = cost;
        set_configuration(best_solution_found, solution->routes, solution->k0);
    }

    for (size_t i = 0; i < solution->instance->k; ++i)
    {
        fprintf(output, "%ld: 0", i);
        for (size_t j = 0; j < solution->k0[i]; ++j)
        {
            fprintf(output, " %ld", solution->routes[i][j]);
        }
        fprintf(output, " 0\n");
    }
    fprintf(output, "Final cost: %f\n", best_cost_found);

    free_solution(solution);
    return best_solution_found;
}
