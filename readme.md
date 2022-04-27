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

## Missing MacOS support

As of right now, only linux and windows are supported. The reason is simple:
I don't have a mac, and hence have no real way to test any code on that platform.

If anyone does, and has some time to spare then by all means: open a pull request.