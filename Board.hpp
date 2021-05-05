#pragma once
#include "City.hpp"
#include "Color.hpp"
#include <iostream>
#include <map>

namespace pandemic
{
    class Board
    {
    private:
        std::map<City, int> _cityMap;

    public:
        int &operator[](City c);
        friend std::ostream &operator<<(std::ostream &os, const Board &b);
        static bool is_clean();
        void remove_cures();
    };
}