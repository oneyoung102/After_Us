#pragma once

#include "game/pages/page.hpp"
#include <optional>


class PageSignal
{
    public :
        std::optional<Page::Name> next_page;
        std::optional<bool> request_capture;

        PageSignal& operator=(const PageSignal& other)
        {
            if(this == &other)
                return *this;
            this->next_page = other.next_page;
            if(this->next_page)//값이 존재해야 함. 즉 페이지 전환이 이루어져야
            {

                if(other.request_capture)
                    this->request_capture = *other.request_capture;
            }
            return *this;
        }
};