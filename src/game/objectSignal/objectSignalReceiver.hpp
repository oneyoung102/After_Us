#pragma once

#include "game/objectSignal/objectSignal.hpp"
#include "tools/cast.hpp"
#include <array>
#include <functional>
#include "tools/hasWHAT.hpp"

template<class T, class ... ARGS>
class ObjectSignalReceiver // FUNC : function, T : enum (last element : COUNT)
{
    private :
        using FUNC = std::function<void(ARGS ...)>;
        std::array<FUNC, tools::CASTs(T::COUNT)> executes;
    public :
        ObjectSignalReceiver()
        {
            static_assert(tools::has_count<T>(), "enum of objectSignalReceiver must have COUNT value.");
        }

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