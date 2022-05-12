#include "crand/crand.h"
#include <iostream>
#include <random>

int main(int argc, char const *argv[])
{
    uint64_t seed;
    randomize(&seed, sizeof seed);
    crand::default_engine rng(seed);
    std::normal_distribution<double> dist(0, 1);
    for (int i = 0; i < 8; i++)
        std::cout << dist(rng) << '\n';    
    return 0;
}
