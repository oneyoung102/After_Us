#pragma once

#include <stdexcept>
#include <type_traits>
#include <vector>
#include <queue>
#include <array>
#include <utility>
#include "game/objectSignal/objectSignal.hpp"
#include "tools/pos.hpp"
#include "tools/dir.hpp"

enum class ButtonCursorSignal
{
    select,
    cursor,
    COUNT
};

template<class T, class P = void>
class has_NONE : public std::false_type {};
template<class T>
class has_NONE<T, std::void_t<decltype(T::NONE)>> : public std::true_type {};


template<size_t R, size_t C, class buttonName>
class ButtonCursor : public ObjectSignal<ButtonCursorSignal> // buttonName에 NONE이 원소로 있어야 함
{
    private : 
        std::array<std::array<std::pair<buttonName,bool>,C>,R> selected;
        tools::POSi cursor;

        const bool cyclic;

        void move_cursor(const tools::POSi& amount)
        {
            selected[cursor.r][cursor.c].second = false;
            cursor += amount;
            cursor = (tools::POSi(C,R)+cursor)%tools::POSi(C,R);

            std::array<std::array<bool,C>,R> visited{{false}};
            std::queue<tools::POSi> coords;
            auto temp_cursor = cursor;
            while(tools::POSi() <= temp_cursor && temp_cursor < tools::POSi(C,R))
            {
                coords.push(temp_cursor);
                temp_cursor += amount;
            }
            while(!coords.empty())
            {
                const auto pos = coords.front();
                coords.pop();
                visited[pos.r][pos.c] = true;
                if(selected[pos.r][pos.c].first != buttonName::NONE)
                {
                    cursor = pos;
                    break;
                }
                for(const auto& dpos : tools::DIR)
                {
                    const auto npos = pos+dpos;
                    if(tools::POSi() <= npos && npos < tools::POSi(C,R) && selected[npos.r][npos.c].first != buttonName::NONE && !visited[npos.r][npos.c])
                        coords.push(npos);
                }
            }
            selected[cursor.r][cursor.c].second = true;
            signal(ButtonCursorSignal::cursor);
        }
    public :
        ButtonCursor(std::vector<std::vector<buttonName>>&& allocated, bool cyclic = false)
            : cyclic(cyclic)
        {
            static_assert(has_NONE<buttonName>::value, "buttonName must have NONE value.");
            
            if(allocated.empty() || allocated.size() != R || allocated[0].size() != C)
                throw std::runtime_error("Button allocated vector is not matched with buttonCursor template variable");
            
            bool init_found = false;
            for(size_t i = 0 ; i < R ; ++i)
                for(size_t j = 0 ; j < C ; ++j)
                    if(!init_found && allocated[i][j] != buttonName::NONE)
                    {
                        selected[i][j] = std::make_pair(allocated[i][j],true);
                        cursor = tools::POSi(j,i);
                        init_found = true;
                    }
                    else
                        selected[i][j] = std::make_pair(allocated[i][j],false);   
            if(!init_found)   
                throw std::runtime_error("Button allocated vector has no button.(only has NONE)");
        }
        void let_select(){signal(ButtonCursorSignal::select);}
        void let_choose_left() 
        {
            if(cursor.c > 0 || cyclic && cursor.c == 0)
                move_cursor(tools::DIR[tools::LEFT]);
        }
        void let_choose_right()
        {
            if(cursor.c < C-1 || cyclic && cursor.c == C-1)
                move_cursor(tools::DIR[tools::RIGHT]);
        }
        void let_choose_up()
        {
            if(cursor.r > 0 || cyclic && cursor.r == 0)
                move_cursor(tools::DIR[tools::UP]);
        }
        void let_choose_down()
        {
            if(cursor.r < R-1 || cyclic && cursor.r == R-1)
                move_cursor(tools::DIR[tools::DOWN]);
        }
        const bool& get_select_status(buttonName type) const
        {
            for(size_t i = 0 ; i < R ; ++i)
                for(size_t j = 0 ; j < C ; ++j)
                    if(selected[i][j].first == type)
                        return selected[i][j].second;
            throw std::runtime_error("factor of function get_select_status is not valid.");
        }
        buttonName get_selected_button(){return selected[cursor.r][cursor.c].first;}
};