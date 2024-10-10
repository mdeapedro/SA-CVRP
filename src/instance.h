#ifndef _INSTANCE_H
#define _INSTANCE_H


typedef struct
{
    // Number of nodes.
    size_t n;

    // Number of vehicles.
    size_t k;

    // Vehicle capacity.
    int q;

    // `demand[i]`: Demand of customer `i`.
    int *demand;

    // `cost[i][j]`: Minimum cost to travel from node `i` to node `j`.
    double **cost;
}
Instance;

Instance *load_instance(const char *filename);

void free_instance(Instance *instance);


#endif // _INSTANCE_H
