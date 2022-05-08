#include "crand/sys_rng.h"
#include <iostream>

#define N   16

int main(int argc, char const *argv[])
{
    uint8_t buf[N] = {0};
    if(crand::randomize(buf, N)){
        std::cerr << "Error\n"; return 1;
    }
    for (size_t i = 0; i < N; i++)
        std::printf("%02X ", buf[i]);
    std::cout << std::endl;
    return 0;
}
