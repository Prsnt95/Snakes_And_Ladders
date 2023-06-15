#include "model.hxx"
#include <catch.hxx>
#include "iostream"

TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}

//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate your functional requirements.
//
TEST_CASE("initial positions") {
    Model model;
    model.lightScore=4;
    model.darkScore=1;
    CHECK(model.playerPositions[Player::light] == 0);
    CHECK(model.playerPositions[Player::dark] == 0);

}

TEST_CASE("Moving the player", "[model]") {
    Model model;
    model.lightScore=4;
    model.darkScore=1;
    model.playerPositions[Player::light] = 1;
    model.die = 2;

    model.move();
    CHECK(model.playerPositions[Player::light] == 3);
    CHECK(model.turn==Player::dark);
}

TEST_CASE("Encountering a snake + toggleTurn") {
    Model model;
    model.lightScore=4;
    model.darkScore=1;
    model.playerPositions[Player::light] = 27;
    model.die = 3;

    model.move();

    CHECK(model.playerPositions[Player::light] == 7);
    CHECK(model.turn==Player::dark);
    model.toggleTurn();
    CHECK(model.turn==Player::light);
}
TEST_CASE("rolling a 6 allows you to roll again") {
    Model model;
    model.lightScore=4;
    model.darkScore=1;
    model.playerPositions[Player::light] = 27;
    model.die = 6;

    model.move();

    CHECK(model.playerPositions[Player::light] == 33);
    CHECK(model.turn==Player::light);
    model.die = 3;
    model.move();
    CHECK(model.playerPositions[Player::light] == 36);
    CHECK(model.turn==Player::dark);
}

TEST_CASE("Encountering a ladder", "[model]") {
    Model model;
    model.lightScore=4;
    model.darkScore=1;
    model.playerPositions[Player::light] = 0;
    model.die = 4;

    model.move();

    CHECK(model.playerPositions[Player::light] == 25);
}

TEST_CASE("Random die rolls", "[model]") {
    Model model;
    model.lightScore=4;
    model.darkScore=1;
    for (int i = 0; i < 100; i++) {
        model.rollDie();
        CHECK(model.die >= 1);
        CHECK(model.die <= 6);
    }
}

TEST_CASE("Winning the game", "[model]") {
    Model model;
    model.lightScore=4;
    model.darkScore=1;
    model.playerPositions[Player::light] = 97;
    model.die = 3;
    model.turn=Player::light;
    CHECK(model.turn==Player::light);
    model.move();

    CHECK(model.playerPositions[Player::light] == 100);
    CHECK(model.turn==Player::neither);
    CHECK(model.winner == Player::light);

}

TEST_CASE("Getting same position as opponent") {
    Model model;
    model.lightScore=4;
    model.darkScore=1;
    model.playerPositions[Player::light] = 3;
    model.playerPositions[Player::dark] = 1;
    CHECK(model.turn==Player::light);
    model.toggleTurn();
    CHECK(model.turn==Player::dark);

    model.die = 2;
    model.move();

    model.turn=Player::dark;
    model.die = 2;
    model.move();

    CHECK(model.playerPositions[Player::light] == 3);
    CHECK(model.playerPositions[Player::dark] == 5);

    CHECK(model.turn==Player::light);

}

TEST_CASE("Bounce Back on empty square") {
    Model model;
    model.lightScore=4;
    model.darkScore=1;
    model.playerPositions[Player::light] = 97;
    model.die = 6;
    model.turn=Player::light;
    CHECK(model.turn==Player::light);
    model.move();

    CHECK(model.playerPositions[Player::light] == 97);

}TEST_CASE("snake from 98 to 55") {
    Model model;
    model.lightScore=4;
    model.darkScore=1;
    model.playerPositions[Player::light] = 97;
    model.die = 1;
    model.turn=Player::light;
    CHECK(model.turn==Player::light);
    model.move();
    CHECK(model.playerPositions[Player::light] == 55);
}

TEST_CASE("Bounce Back on square 98, square with a snake") {
    Model model;
    model.lightScore=4;
    model.darkScore=1;
    model.playerPositions[Player::light] = 97;
    model.die = 5;
    model.turn=Player::light;
    CHECK(model.turn==Player::light);
    model.move();

    CHECK(model.playerPositions[Player::light] == 55);
}

TEST_CASE("Assigning Turn"){
    Model model;

    for (int i = 0; i < 10; i++) {
        model.initialTurnAssigned = false;

        model.lightScore=0;
        model.darkScore=0;


        CHECK(model.playerPositions[Player::light] == 0);
        CHECK(model.playerPositions[Player::dark] == 0);

        CHECK(model.lightScore==0);
        CHECK(model.darkScore==0);
        // std::cout<<"this should  be false: " <<model.initialTurnAssigned<<
                 // "\n";
        model.rollDie();

        // std::cout<<"this should still be false: "
        // <<model.initialTurnAssigned<<
        //          "\n";
        CHECK(model.lightScore!=0);

        CHECK(model.darkScore==0);
        // std::cout<<"light score is: " <<model.lightScore<< "\n";
        model.rollDie();
        // std::cout<<"this should now be true: " <<model.initialTurnAssigned<<
        // "\n";
        CHECK(model.darkScore!=0);
        // std::cout<<"dark score is: " <<model.darkScore<<"\n";

        if(model.lightScore < model.darkScore){
            CHECK(model.turn==Player::dark);
        }
        else if(model.lightScore > model.darkScore){
            CHECK(model.turn==Player::light);
        }

    }

}

