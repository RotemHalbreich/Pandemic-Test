#include "Medic.hpp"

namespace pandemic
{
    //If he treats a city, all the disease cubes will be deleted from that city instead of '1'
    //if there's already a cure for the disease, he automatically cures any city he's in
    //(deletes all cubes) without using "treat" method
    Player &Medic::treat(City c)
    {
        return *this;
    }
}