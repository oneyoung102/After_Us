#pragma once

#include <queue>
#include <stdexcept>
#include <type_traits>


template<class T>
class ObjectSignal //T : enum (last element : COUNT)
{
    private :
        std::queue<T> signals;
    public :
        ObjectSignal()
        {
            static_assert(std::is_enum<T>(),"template type of puyoObjectSignal is not as enum");
        }

        void signal(T signal){signals.push(signal);}
        T giveSignal()
        {
            if(signalEmpty())
                throw std::runtime_error("no signal");
            T signal = signals.front();
            signals.pop();
            return signal;
        }
        bool signalEmpty() const {return signals.empty();}
};