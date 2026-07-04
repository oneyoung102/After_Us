#pragma once

#include <stdexcept>
#include <tuple>

namespace tools
{
    template<class T>
    class Pos
    {
        public :
            union
            {
                struct{T x, y;};
                struct{T c, r;};
            };

            constexpr Pos(T x = static_cast<T>(0), T y = static_cast<T>(0))
                : x(x), y(y)
            {}
            template<class P>
            constexpr Pos(const Pos<P>& other)
                : x(static_cast<T>(other.x))
                , y(static_cast<T>(other.y))
            {
                static_assert(std::is_arithmetic<T>() && std::is_arithmetic<P>(),"Pos non-number type cast is impossible");
            }
            
            template<class P>
            constexpr Pos operator+(const Pos<P>& other) const { return Pos(x + other.x, y + other.y); }
            template<class P>
            constexpr Pos operator-(const Pos<P>& other) const { return Pos(x - other.x, y - other.y); }
            template<class P>
            requires std::is_arithmetic_v<P>
            constexpr Pos operator*(P num) const { return Pos(x * num, y * num); }
            template<class P>
            constexpr Pos operator*(const Pos<P>& other) const { return Pos(x * other.x, y * other.y); }
            template<class P>
            requires std::is_arithmetic_v<P>
            constexpr Pos operator/(P num) const
            {
                if(num == 0)
                    throw std::runtime_error("Pos zero division is impossible");
                return Pos(x / num, y / num);
            }
            template<class P>
            constexpr Pos operator/(const Pos<P>& other) const
            {
                if(other.x == 0 || other.y == 0)
                    throw std::runtime_error("Pos zero division is impossible");
                return Pos(x / other.x, y / other.y);
            }
            constexpr Pos operator%(long long num) const
            {
                if(num == 0)
                    throw std::runtime_error("Pos zero division is impossible");
                return Pos(x % num, y % num);
            }
            constexpr Pos operator%(const Pos<long long>& other) const
            {
                if(other.x == 0 || other.y == 0)
                    throw std::runtime_error("Pos zero division is impossible");
                return Pos(x % other.x, y % other.y);
            }
            template<class P>
            constexpr Pos operator+=(const Pos<P>& other)
            {
                this->x += other.x;
                this->y += other.y;
                return *this;
            }
            template<class P>
            constexpr Pos operator-=(const Pos<P>& other)
            {
                this->x -= other.x;
                this->y -= other.y;
                return *this;
            }
            template<class P>
            requires std::is_arithmetic_v<P>
            constexpr Pos operator*=(P num)
            {
                this->x *= num;
                this->y *= num;
                return *this;
            }
            template<class P>
            requires std::is_arithmetic_v<P>
            constexpr Pos operator/=(P num)
            {
                if(num == 0)
                    throw std::runtime_error("Pos zero division is impossible");
                this->x /= num;
                this->y /= num;
                return *this;
            }
            constexpr Pos operator%=(long long num)
            {
                if(num == 0)
                    throw std::runtime_error("Pos zero division is impossible");
                this->x %= num;
                this->y %= num;
                return *this;
            }
            constexpr inline bool operator==(const Pos& other) const { return this->x == other.x && this->y == other.y; }
            constexpr inline bool operator!=(const Pos& other) const { return this->x != other.x || this->y != other.y; }
            constexpr inline bool operator<(const Pos& other) const { return this->x < other.x && this->y < other.y; }
            constexpr inline bool operator>(const Pos& other) const { return this->x > other.x && this->y > other.y; }
            constexpr inline bool operator<=(const Pos& other) const { return this->x <= other.x && this->y <= other.y; }
            constexpr inline bool operator>=(const Pos& other) const { return this->x >= other.x && this->y >= other.y; }
            constexpr inline bool operator==(Pos&& other) const { return this->x == other.x && this->y == other.y; }
            constexpr inline bool operator!=(Pos&& other) const { return this->x != other.x || this->y != other.y; }
            constexpr inline bool operator<(Pos&& other) const { return this->x < other.x && this->y < other.y; }
            constexpr inline bool operator>(Pos&& other) const { return this->x > other.x && this->y > other.y; }
            constexpr inline bool operator<=(Pos&& other) const { return this->x <= other.x && this->y <= other.y; }
            constexpr inline bool operator>=(Pos&& other) const { return this->x >= other.x && this->y >= other.y; }
    };

    using POSs = Pos<size_t>;
    using POSi = Pos<int>;
    using POSf = Pos<float>;

    template<std::size_t I, class T>
    constexpr auto& get(Pos<T>& p)
    {
        if constexpr (I == 0) return p.x;
        else return p.y;
    }

    template<std::size_t I, class T>
    constexpr const auto& get(const Pos<T>& p)
    {
        if constexpr (I == 0) return p.x;
        else return p.y;
    }
}
namespace std
{
    template<class T>
    struct tuple_size<tools::Pos<T>> : std::integral_constant<size_t, 2> {};

    template<class T>
    struct tuple_element<0, tools::Pos<T>> { using type = T; };
    template<class T>
    struct tuple_element<1, tools::Pos<T>> { using type = T; };
}