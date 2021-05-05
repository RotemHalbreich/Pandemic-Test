#include "Dispatcher.hpp"

namespace pandemic
{
    //if he's in a research station, he can fly directly to any city without tossing a card
    Player &Dispatcher::fly_direct(City c)
    {
        return *this;
    }
}