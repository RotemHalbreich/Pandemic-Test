#include "Board.hpp"

using namespace std;

namespace pandemic
{
    int &Board::operator[](City c) { return _cityMap[c]; }

    std::ostream &operator<<(std::ostream &os, const Board &b) { return os; }

    bool Board::is_clean() { return true; }

    void Board::remove_cures() {}
}