#pragma once
#include <type_traits>

namespace tools
{
    template<class T, class P = void>
    class has_NONE : public std::false_type {};
    template<class T>
    class has_NONE<T, std::void_t<decltype(T::NONE)>> : public std::true_type {};

    template<class T>
    constexpr bool has_none() {return has_NONE<T>::value;}

    template<class T, class P = void>
    class has_COUNT : public std::false_type {};
    template<class T>
    class has_COUNT<T, std::void_t<decltype(T::COUNT)>> : public std::true_type {};
    template<class T>
    constexpr bool has_count() {return has_COUNT<T>::value;}
}