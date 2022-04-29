# crand

Random numbers, they're everywhere. I just felt like implementing a few random generators (other than the ones
already included in the standards), so here it is.

**crand** is a general purpose RNG library, available in both C and C++.

## Features

- Support for a lot of platforms including windows, linux, mac and other unix based operating systems
- Simple interfaces for both C and C++ versions

## Documentation

Coming soon

## Getting started

### Quick Example

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

## Compiling and linking

To compile, just link against the library file for your platform.
You can either download the binaries from the [latest release](https://github.com/EddieBreeg/rand/releases/tag/v1.0)
or compile from source.\
Do note that if you're planning to do the latter on windows, you will need to install 
bcrypt separately. The cryptographic provider SDK from microsoft can be found [here](https://www.microsoft.com/en-us/download/details.aspx?id=30688).