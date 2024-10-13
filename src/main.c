#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sa.h"


int main(int argc, char **argv)
{
    if (argc < 2) return 1;

    Instance *instance = load_instance(argv[1]);
    if (!instance) return 1;

    InputParameters ip = { instance, 10, time(NULL) };
    OutputParameters op = { stdout };
    SA_Parameters sap = { 0.99999, 1.0 };

    Solution *solution = sa_solve(ip, op, sap);

    free_solution(solution);
    free_instance(instance);
}
