#include <stdio.h>
#include <stdlib.h>

#include "instance.h"


Instance *load_instance(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        return NULL;
    }

    Instance *instance = malloc(sizeof(Instance));

    char word[128];
    fscanf(file, "%127s", word);
    instance->n = atoi(word);

    instance->demand = malloc(instance->n * sizeof(int));

    instance->cost = malloc(instance->n * sizeof(double *));
    for (size_t i = 0; i < instance->n; ++i)
    {
        instance->cost[i] = malloc(instance-> n * sizeof(double));
    }

    fscanf(file, "%127s", word);
    instance->k = atoi(word);

    fscanf(file, "%127s", word);
    instance->q = atoi(word);

    for (size_t i = 0; i < instance->n; ++i)
    {
        fscanf(file, "%127s", word);
        instance->demand[i] = atoi(word);
        for (size_t j = 0; j < instance->n; ++j)
        {
            fscanf(file, "%127s", word);
            instance->cost[i][j] = atof(word);
        }
    }

    fclose(file);

    instance->filename = (char *)filename;

    return instance;
}

void free_instance(Instance *instance)
{
    if (instance == NULL)
    {
        return;
    }

    for (size_t i = 0; i < instance->n; ++i)
    {
        free(instance->cost[i]);
    }
    free(instance->cost);
    free(instance->demand);
    free(instance);
}
