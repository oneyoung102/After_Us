#pragma once

#include "game/objectSignal/objectSignal.hpp"
#include "tools/cast.hpp"
#include <array>
#include <functional>

template<class T, class ... ARGS>
class ObjectSignalReceiver // FUNC : function, T : enum (last element : COUNT)
{
    private :
        using FUNC = std::function<void(ARGS ...)>;
        std::array<FUNC, tools::CASTs(T::COUNT)> executes;
    public :
        ObjectSignalReceiver(){}

        void execute(ObjectSignal<T>& object_signal, ARGS ... args)
        {
            while(!object_signal.signalEmpty())
            {
                const auto idx = tools::CASTs(object_signal.giveSignal());
                if(executes[idx])
                    executes[idx](args ...);
            }
        }
        void addExecute(T signal, FUNC&& execute)
        {
            executes[tools::CASTs(signal)] = std::move(execute);
        }
};