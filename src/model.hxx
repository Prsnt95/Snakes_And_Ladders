#pragma once

#include <ge211.hxx>
#include "iostream"
#include "stdio.h"
#include <unordered_map>
enum class Player {
    neither,
    light,
    dark
};

class Model
{
private:

    std::unordered_map<int, std::string> board;
    std::unordered_map<int, int> snakes;
    std::unordered_map<int, int> ladders;

public:
    std::unordered_map<int, int> positions;
    Model();
    void bounce_back();
    void toggleTurn();
    void checkWin();
    void move();
    void rollDie();
    void setTurn();


    // Add other getter and setter functions




    std::unordered_map<Player, int> playerPositions;
    Player turn;
    Player winner;
    int die;
    int lightScore ;
    int darkScore;
    bool initialTurnAssigned;

};
