# rand

Random numbers, they're everywhere. And since generating good quality random data 
is by no means an easy task, leaving it to your system is probably the safest bet.

This library is just that: a single function wrapper that allows you to generate
random bytes without having to worry about system calls.

## Usage

*Check out [test.c](test.c) to see the full code*
```c
#include "rand.h"
#include <stdio.h>

#define N   512

int main(int argc, char const *argv[])
{
    unsigned char foo[N] = {0};
    randomize(foo, N);

    // do stuff...
}
```

To compile, just link against the library file for your platform.
You can either download the binaries from the [latest release](https://github.com/EddieBreeg/rand/releases/tag/v1.0)
or compile from source.\
Do note that if you're planning to do the latter on windows, you will need to install 
bcrypt separately. The cryptographic provider SDK from microsoft can be found [here](https://www.microsoft.com/en-us/download/details.aspx?id=30688).