#pragma once

#include <type_traits>

namespace crand
{
    #if __cplusplus >= 2020
    template<typename T> requires 
        (std::is_integral<T>::value && std::is_unsigned<T>::value)
    #else
    template<typename T>
    #endif
    class prng
    {
    private:
    public:
        using result_type = T;
        virtual result_type operator()() = 0;
        static constexpr result_type min();
        static constexpr result_type max();

    };
    
    
} // namespace crand
