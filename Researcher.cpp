#include "Researcher.hpp"

namespace pandemic
{
    //Can discover a cure in any city, even if there isn't a research station in it
    Player &Researcher::discover_cure(Color c)
    {
        return *this;
    }
}