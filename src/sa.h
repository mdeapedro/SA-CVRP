#ifndef _SA_H
#define _SA_H


#include <stdio.h>

#include "solution.h"


typedef struct
{
    FILE *output;
} OutputParameters;

typedef struct
{
    Instance *instance;
    unsigned int time_limit_seconds;
    unsigned int seed;

} InputParameters;

typedef struct
{
    double initial_temperature;
    double alpha;
} SA_Parameters;

Solution *sa_solve(const InputParameters ip, const OutputParameters op, const SA_Parameters sap);


#endif // _SA_H
