# crand

Random numbers, they're everywhere. I just felt like implementing a few random generators (other than the ones
already included in the standards), so here it is.

**crand** is a general purpose RNG library, available in both C and C++.

## Features

- Support for a lot of platforms including windows, linux, mac and other unix based operating systems
- Simple interfaces for both C and C++ versions

### List of supported RNGs

**Non Cryptographic RNGs**

- `lfsr128`
- `xorshift32`
- `xorshift64`
- `xorshift64`
- `xoshiro256**`

**Cryptographic RNGs**

Historically, a few cryptographic RNG designs have been created. Most of them are based on cryptographic
primitives (eg block ciphers). Some, like RC4, have been proven to be insecure and were therefore not included
in this library. Others have other drawbacks like efficiency. The TLDR being that although there are many
different designs, having a short list of good common ones is enough. For crand, said list is the following:

- `CTR-AES256` (AES256 running in counter mode)
- `ChaCha20`

**Non deterministic RNG**

Additionally to the pseudo-random generators, crand also provides an interface to generate 
true random data. There are a few things to note about this RNG though:
- it is slow, because it depends on the system's ability to gather entropy. DO NOT USE this function
to generate large amounts of data, as it can't be guaranteed that the calls won't block
- the C version supports *most* platforms (Linux, UNIX based, Mac, Windows), but it's always
possible to find some specific platforms on which the code either won't run, or won't compile at all
- the C++ version uses std::random_device to provide the non deterministic generator. The C++ standard
does NOT guarantee that said device is ACTUALLY non deterministic, although it will be on most platforms
(namely the ones mentionned above). It is strongly encouraged that you test it on a target platform before
using in production, ESPECIALLY for cryptographic purposes. 

Assuming it runs fine and does indeed produce non-deterministic sequences, this generator 
can be used to generate things like cryptographic keys, nonces, or to seed other pseudo-random
engines.

## Documentation

All the [header files](include) have been carefully commented:

- [<crand/crand.h>](include/crand/crand.h)
- [<crand/ctr.h>](include/crand/ctr.h)
- [<crand/lfsr.h>](include/crand/lfsr.h)
- [<crand/xoshiro.h>](include/crand/xoshiro.h)
- [<crand/xorshift.h>](include/crand/xorshift.h)
- [<crand/chacha20/chacha20.h>](include/crand/chacha20/chacha20.h)

### Regarding the C++ API

All C++ classes are placed in the `crand` namespace. All the non-cryptographic PRNGs inherit from the 
abstract `prng` class, which complies with the *UniformRandomBitGenerator* requirements from the standard
C++ library. That means any of the mentionned classes can be used with standard distributions and so on.

Here's an example of how that would work:

```cpp
#include "crand/crand.h"
#include <iostream>
#include <random>

int main(int argc, char const *argv[])
{
    crand::default_engine rng(0);
    std::uniform_real_distribution<double> dist;
    for (int i = 0; i < 8; i++)
        std::cout << dist(rng) << '\n';    
    return 0;
}
```

## Getting started

### Quick Example

```cpp
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
```

## Compiling and linking

To compile, just link against the library file for your platform.
You can either download the binaries from the [latest release](https://github.com/EddieBreeg/crand/releases/tag/1.1)
or compile from source.\
Do note that if you're planning to do the latter on windows, you will need to install 
bcrypt separately. The cryptographic provider SDK from microsoft can be found [here](https://www.microsoft.com/en-us/download/details.aspx?id=30688).
