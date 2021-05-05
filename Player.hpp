#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <set>

namespace pandemic
{
    class Player
    {
    protected:
        Board &_board;
        std::set<City> _cards;
        City _city;
        std::string _role;

    public:
        Player(Board &board, City city, std::string role) : _board(board), _city(city), _role(role) {}

        Player &drive(City c);
        Player &fly_charter(City c);
        Player &fly_shuttle(City c);
        Player &take_card(City c);
        std::string role();

        //virtual functions
        virtual Player &discover_cure(Color c);
        virtual Player &treat(City c);
        virtual Player &build();
        virtual Player &fly_direct(City c);
    };
}