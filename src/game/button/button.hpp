#pragma once

#include "game/button/buttonCursor.hpp"
#include "game/letManager/letManager.hpp"
#include "game/objectSignal/objectSignalReceiver.hpp"
#include "resourceManager/soundManager/soundManager.hpp"
#include <functional>

class FileManager;
class LetManager;

template<size_t R, size_t C, class buttonName>
class Button
{
    private :
        bool __selected;
        ObjectSignalReceiver<ButtonCursorSignal,FileManager&> signalReceiver;
    public :
        ButtonCursor<R,C,buttonName> cursor;
        
        Button(std::vector<std::vector<buttonName>>&& allocated, bool cyclic = false)
            : cursor(std::move(allocated), cyclic)
            , __selected(false)
        {}
        void setExecutes(SoundManager& ps, LetManager& pl)
        {
            signalReceiver.addExecute(ButtonCursorSignal::cursor, [&ps](FileManager& pfs){
                //ps.play_sound(pfs.get_buffer(fileManager::Sound::cursor));
            });
            signalReceiver.addExecute(ButtonCursorSignal::select, [&ps,&pl,this](FileManager& pfs){
                if(!ps.is_empty())
                    ps.clear_back();
                //ps.play_sound(pfs.get_buffer(fileManager::Sound::select));
                pl.clear();
                __selected = true;
            });
        }
        void addExecutes(ButtonCursorSignal signal, std::function<void(FileManager&)>&& func)
        {
            signalReceiver.addExecute(signal, std::move(func));
        }
        void receiveSignals(FileManager& pfs)
        {
            signalReceiver.execute(cursor, pfs);
        }
        
        bool selected()
        {
            const bool temp_selected = __selected;
            __selected = false;
            return temp_selected;
        }
};