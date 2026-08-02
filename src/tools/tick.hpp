#pragma once

namespace tools
{
    class Tick
    {
        private :
            int tick;
        public:
            static constexpr int FRAMERATE = 120;

            Tick(float second = 0)
                : tick(second*FRAMERATE)
            {}
            ~Tick() = default;
            Tick& operator=(const Tick& other) noexcept {tick = other.tick; return *this;}
            Tick& operator=(int value) noexcept {tick = value; return *this;}

            operator int() const {return tick;}
            operator float() const {return tick;}


            int operator+(int value) const {return tick+value;}
            int operator-(int value) const {return tick-value;}
            int operator*(int value) const {return tick*value;}
            int operator/(int value) const {return (tick+0.0)/value;}
            int operator%(int value) const {return tick%value;}

            int operator+(const Tick& other) const {return tick+other.tick;}
            int operator-(const Tick& other) const {return tick-other.tick;}
            int operator*(const Tick& other) const {return tick*other.tick;}
            int operator/(const Tick& other) const {return (tick+0.0)/other.tick;}
            int operator%(const Tick& other) const {return tick%other.tick;}

            Tick& operator+=(int value) noexcept {tick += value; return *this;}
            Tick& operator-=(int value) noexcept {tick -= value; return *this;}
            Tick& operator*=(int value) noexcept {tick *= value; return *this;}
            Tick& operator/=(int value) noexcept {tick /= value; return *this;}
            Tick& operator%=(int value) noexcept {tick %= value; return *this;}
            
            Tick& operator+=(const Tick& other) noexcept {tick += other.tick; return *this;}
            Tick& operator-=(const Tick& other) noexcept {tick -= other.tick; return *this;}
            Tick& operator*=(const Tick& other) noexcept {tick *= other.tick; return *this;}
            Tick& operator/=(const Tick& other) noexcept {tick /= other.tick; return *this;}
            Tick& operator%=(const Tick& other) noexcept {tick %= other.tick; return *this;}

            Tick& operator--() noexcept {tick--; return *this;}
            Tick& operator++() noexcept {tick++; return *this;}
            Tick operator--(int) noexcept {Tick temp = *this; tick--; return temp;}
            Tick operator++(int) noexcept {Tick temp = *this; tick++; return temp;}
            
            bool operator==(int value) const noexcept {return tick == value;}
            bool operator!=(int value) const noexcept {return tick != value;}
            bool operator<(int value) const noexcept {return tick < value;}
            bool operator>(int value) const noexcept {return tick > value;}
            bool operator<=(int value) const noexcept {return tick <= value;}
            bool operator>=(int value) const noexcept {return tick >= value;}

            bool operator==(const Tick& other) const noexcept {return tick == other.tick;}
            bool operator!=(const Tick& other) const noexcept {return tick != other.tick;}
            bool operator<(const Tick& other) const noexcept {return tick < other.tick;}
            bool operator>(const Tick& other) const noexcept {return tick > other.tick;}
            bool operator<=(const Tick& other) const noexcept {return tick <= other.tick;}
            bool operator>=(const Tick& other) const noexcept {return tick >= other.tick;}

            static float to_second(int value){return (float)value/FRAMERATE;}
            float to_second() const {return (float)tick/FRAMERATE;}
            
    };
}