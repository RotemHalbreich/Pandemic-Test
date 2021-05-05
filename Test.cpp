#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include "doctest.h"

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Medic.hpp"
#include "Dispatcher.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "Virologist.hpp"
#include "OperationsExpert.hpp"

using namespace std;
using namespace pandemic;

TEST_CASE("drive()")
{
    Board board;
    Player p(board, Bogota, "Medic");
    CHECK_NOTHROW(p.drive(Miami));        //a neighbor city
    CHECK_THROWS(p.drive(BuenosAires));   //not a neighbor city
    CHECK_THROWS(p.drive(HoChiMinhCity)); //not a neighbor city
    CHECK_NOTHROW(p.drive(Lima));         //neighbor city
    CHECK_NOTHROW(p.drive(SaoPaulo));     //neighbor city
}

TEST_CASE("fly_direct()")
{
    Board board;
    Player p(board, Bogota, "Virologist");
    p.take_card(Karachi);
    CHECK_NOTHROW(p.fly_direct(Karachi)); // can fly Karachi
    CHECK_THROWS(p.fly_direct(Seoul));    // can't fly Seoul
    p.take_card(Seoul);
    CHECK_NOTHROW(p.fly_direct(Seoul)); // can fly Seoul
    CHECK_THROWS(p.fly_direct(Seoul));  // already in Seoul
}

TEST_CASE("fly_charter()")
{
    Board board;
    Player p(board, Bogota, "Scientist");
    CHECK_THROWS(p.fly_charter(Jakarta)); //can't fly to Jakarta because there's no card of Bogota
    p.take_card(Bogota);
    CHECK_NOTHROW(p.fly_charter(Osaka)); // can fly Osaka
    p.take_card(Seoul);
    CHECK_THROWS(p.fly_charter(Seoul)); // can't fly Seoul from Osaka because there's no card of Osaka
    p.take_card(Osaka);
    CHECK_THROWS(p.fly_charter(Osaka)); // already in Osaka
}

TEST_CASE("fly_shuttle() + build()")
{
    Board board;
    Player p(board, Bogota, "Scientist");
    CHECK_THROWS(p.fly_shuttle(London)); //can't fly without a card and station
    CHECK_THROWS(p.build());             //can't build a station without a card
    p.take_card(Bogota);
    CHECK_NOTHROW(p.build()); //builds a station in Bogota
    CHECK_NOTHROW(p.drive(Miami));
    CHECK_NOTHROW(p.drive(Washington));
    p.take_card(Washington);
    CHECK_THROWS(p.fly_shuttle(Bogota));  //can't fly to Bogota because Washington doesn't have a station yet
    CHECK_NOTHROW(p.build());             //builds a station in Washington
    CHECK_NOTHROW(p.fly_shuttle(Bogota)); //can fly to Bogota from Washington because they both have a station
}

TEST_CASE("discover_cure()")
{
    Board board;
    Player p(board, Moscow, "Medic");
    CHECK_THROWS(p.discover_cure(Black)); //can't discover the cure because we don't have 5 cards from the same color and there's no a station in Moscow
    p.take_card(Moscow);
    CHECK_NOTHROW(p.build()); // builds a station in Moscow (BLACK city)
    p.take_card(SanFrancisco);
    p.fly_direct(SanFrancisco);
    p.take_card(SanFrancisco);
    CHECK_NOTHROW(p.build()); // builds a station in SanFrancisco (BLUE city)
    p.take_card(Tehran);
    p.take_card(Moscow);
    p.take_card(Delhi); // takes 3 BLACK cards
    p.take_card(Tehran);
    p.take_card(Moscow);                  // takes more 2 BLUE cards (5 cards in total)
    CHECK_THROWS(p.discover_cure(Black)); // can't find a cure because we don't have enough BLACK cards
    p.take_card(Kolkata);
    p.take_card(Algiers);                  // takes 2 more BLACK cards (5 BLACK + 2 BLUE in total)
    CHECK_NOTHROW(p.discover_cure(Black)); // can discover a cure for a BLACK disease
}