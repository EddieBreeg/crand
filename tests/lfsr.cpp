#include "crand/lfsr.h"
#include <stdio.h>
#include <random>
#include <iostream>

int main(int argc, char const *argv[])
{
    crand::lfsr128 lfsr((uint64_t)main);
    std::uniform_int_distribution<unsigned int> dist;
    std::cout << dist(lfsr) << '\n';
    return 0;
}
