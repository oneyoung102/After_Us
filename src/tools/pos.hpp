#pragma once

#include <stdexcept>
#include <tuple>

namespace tools
{
    template<class T>
    class POS
    {
        public :
            union
            {
                struct{T x, y;};
                struct{T c, r;};
            };

            constexpr POS(T x = static_cast<T>(0), T y = static_cast<T>(0))
                : x(x), y(y)
            {}
            template<class P>
            constexpr POS(const POS<P>& other)
                : x(static_cast<T>(other.x))
                , y(static_cast<T>(other.y))
            {
                static_assert(std::is_arithmetic<T>() && std::is_arithmetic<P>(),"POS non-number type cast is impossible");
            }
            
            constexpr POS operator+(const POS& other) const { return POS(x + other.x, y + other.y); }
            constexpr POS operator-(const POS& other) const { return POS(x - other.x, y - other.y); }
            constexpr POS operator*(T num) const { return POS(x * num, y * num); }
            constexpr POS operator*(const POS& other) const { return POS(x * other.x, y * other.y); }
            constexpr POS operator/(T num) const
            {
                if(num == 0)
                    throw std::runtime_error("POS zero division is impossible");
                return POS(x / num, y / num);
            }
            constexpr POS operator/(const POS& other) const
            {
                if(other.x == 0 || other.y == 0)
                    throw std::runtime_error("POS zero division is impossible");
                return POS(x / other.x, y / other.y);
            }
            constexpr POS operator%(T num) const
            {
                if(num == 0)
                    throw std::runtime_error("POS zero division is impossible");
                return POS(x % num, y % num);
            }
            constexpr POS operator%(const POS& other) const
            {
                if(other.x == 0 || other.y == 0)
                    throw std::runtime_error("POS zero division is impossible");
                return POS(x % other.x, y % other.y);
            }
            constexpr POS operator+=(const POS& other)
            {
                this->x += other.x;
                this->y += other.y;
                return *this;
            }
            constexpr POS operator-=(const POS& other)
            {
                this->x -= other.x;
                this->y == other.y;
                return *this;
            }
            constexpr POS operator*=(T num)
            {
                this->x *= num;
                this->y *= num;
                return *this;
            }
            constexpr POS operator/=(T num) const
            {
                if(num == 0)
                    throw std::runtime_error("POS zero division is impossible");
                this->x /= num;
                this->y /= num;
                return *this;
            }
            constexpr POS operator%=(T num) const
            {
                if(num == 0)
                    throw std::runtime_error("POS zero division is impossible");
                this->x %= num;
                this->y %= num;
                return *this;
            }
            constexpr bool operator==(const POS& other) const { return other.x == this->x && other.y == this->y; }
            constexpr bool operator!=(const POS& other) const { return other.x != this->x || other.y != this->y; }
            constexpr bool operator<(const POS& other) const { return other.x < this->x && other.y < this->y; }
            constexpr bool operator>(const POS& other) const { return other.x > this->x && other.y > this->y; }
            constexpr bool operator<=(const POS& other) const { return other.x <= this->x && other.y <= this->y; }
            constexpr bool operator>=(const POS& other) const { return other.x >= this->x && other.y >= this->y; }
    };

    using POSs = POS<size_t>;
    using POSi = POS<int>;
    using POSf = POS<float>;

    template<std::size_t I, class T>
    constexpr auto& get(POS<T>& p)
    {
        if constexpr (I == 0) return p.x;
        else return p.y;
    }

    template<std::size_t I, class T>
    constexpr const auto& get(const POS<T>& p)
    {
        if constexpr (I == 0) return p.x;
        else return p.y;
    }
}
namespace std
{
    template<class T>
    struct tuple_size<tools::POS<T>> : std::integral_constant<size_t, 2> {};

    template<class T>
    struct tuple_element<0, tools::POS<T>> { using type = T; };
    template<class T>
    struct tuple_element<1, tools::POS<T>> { using type = T; };
}