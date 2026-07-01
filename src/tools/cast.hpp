#pragma once

#include <cstdlib>

namespace tools
{

    template <typename T>
    inline constexpr int CASTi(T x) { return static_cast<int>(x); }

    template <typename T>
    inline constexpr float CASTf(T x) { return static_cast<float>(x); }

    template <typename T>
    inline constexpr size_t CASTs(T x) { return static_cast<size_t>(x); }

}
