#include "Virologist.hpp"

namespace pandemic
{
    //Can treat any city even if she's not in it, after tossing it's card
    Player &Virologist::treat(City c)
    {
        return *this;
    }
}