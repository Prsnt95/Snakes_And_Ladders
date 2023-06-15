#include "model.hxx"
#include <cstdlib>  // For rand() function
#include <random>
#include <unordered_map>

Model::Model() {
    playerPositions = {
            {Player::light, 0},
            {Player::dark, 0}
    };
    die = 0;

    turn = Player::light;
    winner = Player::neither;

    // used to assign first turn
    lightScore=0;
    darkScore=0;

    initialTurnAssigned=false;



    //NEEDS TO BE UPDATES WITH MORE SNAKES AND LADDER


    // snakes = {
    //         {19, 7}, {54, 34}, {62, 10},
    //         {87, 24}, {95, 75}, {99, 78}
    // };
    board = {
            {1, "Empty"}, {2, "Empty"}, {3, "Empty"},
            {4, "LadderBottom"}, {5, "Empty"}, {6, "Empty"},
            {7, "SnakeTail"}, {8, "Empty"}, {9, "Empty"},
            {10, "Empty"}, {11, "Empty"}, {12, "Empty"},
            {13, "Empty"}, {14, "Empty"}, {15, "SnakeTail"},
            {16, "Empty"}, {17, "Empty"}, {18, "Empty"},
            {19, "SnakeTail"}, {20, "Empty"}, {21, "LadderBottom"},
            {22, "Empty"}, {23, "Empty"}, {24, "Empty"},
            {25, "LadderTop"}, {26, "Empty"}, {27, "Empty"},
            {28, "Empty"}, {29, "LadderBottom"}, {30, "SnakeHead"},
            {31, "Empty"}, {32, "Empty"}, {33, "Empty"},
            {34, "Empty"}, {35, "Empty"}, {36, "Empty"},
            {37, "Empty"}, {38, "Empty"}, {39, "LadderTop"},
            {40, "Empty"}, {41, "Empty"}, {42, "SnakeTail"},
            {43, "LadderBottom"}, {44, "Empty"}, {45, "Empty"},
            {46, "Empty"}, {47, "SnakeHead"}, {48, "Empty"},
            {49, "Empty"}, {50, "Empty"}, {51, "SnakeTail"},
            {52, "Empty"}, {53, "Empty"}, {54, "Empty"},
            {55, "SnakeTail"}, {56, "SnakeHead"}, {57, "Empty"},
            {58, "Empty"}, {59, "Empty"}, {60, "Empty"},
            {61, "Empty"}, {62, "Empty"}, {63, "LadderBottom"},
            {64, "Empty"}, {65, "Empty"}, {66, "Empty"},
            {67, "Empty"}, {68, "Empty"}, {69, "Empty"},
            {70, "Empty"}, {71, "LadderBottom"}, {72, "Empty"},
            {73, "SnakeHead"}, {74, "LadderTop"}, {75, "SnakeTail"},
            {76, "LadderTop"}, {77, "Empty"}, {78, "Empty"},
            {79, "Empty"}, {80, "LadderTop"}, {81, "Empty"},
            {82, "SnakeHead"}, {83, "Empty"}, {84, "Empty"},
            {85, "Empty"}, {86, "Empty"}, {87, "Empty"},
            {88, "Empty"}, {89, "LadderTop"}, {90, "Empty"},
            {91, "Empty"}, {92, "SnakeHead"}, {93, "Empty"},
            {94, "Empty"}, {95, "Empty"}, {96, "Empty"},
            {97, "Empty"}, {98, "SnakeHead"}, {99, "Empty"},
            {100, "Empty"}
    };

    positions = {
            {1, 1}, {2, 2}, {3, 3},
            {4, 4}, {5, 5}, {6, 6},
            {7, 7}, {8, 8}, {9, 9},
            {10, 10}, {11, 11}, {12, 12},
            {13, 13}, {14, 14}, {15, 15},
            {16, 16}, {17, 17}, {18, 18},
            {19, 19}, {20, 20}, {21, 21},
            {22, 22}, {23, 23}, {24, 24},
            {25, 25}, {26, 26}, {27, 27},
            {28, 28}, {29, 29}, {30, 30},
            {31, 31}, {32, 32}, {33, 33},
            {34, 34}, {35, 35}, {36, 36},
            {37, 37}, {38, 38}, {39, 39},
            {40, 40}, {41, 41}, {42, 42},
            {43, 43}, {44, 44}, {45, 45},
            {46, 46}, {47, 47}, {48, 48},
            {49, 49}, {50, 50}, {51, 51},
            {52, 52}, {53, 53}, {54, 54},
            {55, 55}, {56, 56}, {57, 57},
            {58, 58}, {59, 59}, {60, 60},
            {61, 61}, {62, 62}, {63, 63},
            {64, 64}, {65, 65}, {66, 66},
            {67, 67}, {68, 68}, {69, 69},
            {70, 70}, {71, 71}, {72, 72},
            {73, 73}, {74, 74}, {75, 75},
            {76, 76}, {77, 77}, {78, 78},
            {79, 79}, {80, 80}, {81, 81},
            {82, 82}, {83, 83}, {84, 84},
            {85, 85}, {86, 86}, {87, 87},
            {88, 88}, {89, 89}, {90, 90},
            {91, 91}, {92, 92}, {93, 93},
            {94, 94}, {95, 95}, {96, 96},
            {97, 97}, {98, 98}, {99, 99},
            {100, 100}
    };

    // snakes: {SnakeHead,SnakeTail}
    snakes = {
            {positions[30], positions[7]},
            {positions[47], positions[15]},
            {positions[56], positions[19]},
            {positions[73], positions[51]},
            {positions[82], positions[42]},
            {positions[92], positions[75]},
            {positions[98], positions[55]}
    };

    ladders = {
            {positions[4], positions[25]},
            {positions[21], positions[39]},
            {positions[29], positions[74]},
            {positions[43], positions[76]},
            {positions[63], positions[80]},
            {positions[71], positions[89]}
    };


}

void Model::setTurn() {
    if (lightScore > darkScore && darkScore != 0) {
        turn = Player::light;
    } else if (darkScore > lightScore && lightScore != 0) {
        turn = Player::dark;
    } else {
        // If scores are equal or one of the scores is zero,
        // randomize the first turn
        turn = (rand() % 2 == 0) ? Player::light : Player::dark;
    }
}

void Model::toggleTurn() {
    turn = (turn == Player::light) ? Player::dark : Player::light;
}


void Model::bounce_back() {
    int currentPosition = playerPositions[turn];
    int excess = currentPosition - 100;
    int newPosition = 100 - excess;
    playerPositions[turn] = newPosition;

    if (board[newPosition] == "SnakeHead") {
        playerPositions[turn] = snakes[newPosition];
    } else if (board[newPosition] == "LadderBottom") {
        playerPositions[turn] = ladders[newPosition];
    }

}


void Model::checkWin() {
    int currentPosition = playerPositions[turn];
    if (currentPosition >= 100) {
        if (currentPosition > 100) {
            bounce_back();

        } else {
            winner = turn;
            turn = Player::neither;
        }

        // Call win() function or perform other actions after a win
    }
}



void Model::move() {

    int currentPosition = playerPositions[turn];
    int newPosition = currentPosition + die;

    if (newPosition <= 100) {
        playerPositions[turn] = newPosition;
        checkWin();

        if (board[newPosition] == "SnakeHead") {
            playerPositions[turn] = snakes[newPosition];
        } else if (board[newPosition] == "LadderBottom") {
            playerPositions[turn] = ladders[newPosition];
        }

        if (newPosition != currentPosition && die!=6) {
            toggleTurn();
        }

        checkWin();
    }

    else{
        playerPositions[turn] = newPosition;
        checkWin();
    }

}

void Model::rollDie() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 6);

    die = dis(gen);
    if (lightScore == 0) {
        lightScore = die;
        toggleTurn();
    } else if (darkScore == 0) {
        darkScore = die;
    } else {
        move();
    }
    if (lightScore != 0 && darkScore != 0 && !initialTurnAssigned) {
        setTurn();
        initialTurnAssigned = true; // Set initialTurnAssigned to
        // true after the first turn is assigned
    } else if (lightScore == 0 && darkScore == 0) {
        setTurn();  // Call setTurn() when both scores are set to zero
    }
}



