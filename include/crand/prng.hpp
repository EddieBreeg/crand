#pragma once

#include <type_traits>

namespace crand
{
    #if __cplusplus >= 2020
    template<typename T> requires 
        (std::is_integral<T>::value && std::is_unsigned<T>::value)
    #else
    /* Represents a pseudo-random number generator, that complies with the UniformRandomBitGenerator
    standard requirements. All non-cryptographic PRNGs in crand inherit from this class. */
    template<typename T>
    #endif
    class prng 
    {
    protected:
        prng() {}; /* default constructor, only here because needed by prng's subclasses */
    public:
        using result_type = T; /* The type of value generated. Must be an unsigned integral type */
        virtual result_type operator()() = 0; /* Generates the next value in the pseudo-random sequence */
        static constexpr result_type min(); /* Returns the minimum possible value the generator can produce */
        static constexpr result_type max(); /* Returns the maximum possible value the generator can produce */
        prng(const prng<T>&) = delete;
        prng<T>& operator=(const prng<T>&) = delete;
    };
    
    
} // namespace crand
