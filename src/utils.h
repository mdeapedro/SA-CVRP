#ifndef _UTILS_H
#define _UTILS_H


// Return a random int in [a, b[.
static inline int random_ab(int a, int b)
{
    return (rand() % (b - a)) + a;
}

// Return a random double in [0, 1]
static inline double random_01()
{
    return (double)rand()/RAND_MAX;
}

#endif // _UTILS_H
