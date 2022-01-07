#pragma once

#include <vector>
#include <iostream>
using namespace std;

#include "player.h"
#include "map.h"
#include "bomb.h"

// Class Game, which contains all the variables related to the game
class Game{
public:

    Game();

    // Shows the introduction screen
    void intro_screen();

    // Shows the explanation screen
    void explanation_screen();

    // Starts the game
    void start();

    // Main loop of the game
    void loop();

    // Shows the end screen
    void end_of_game_screen();

    // Vector of pointers to each player in the game
    vector<Player*> players;

    // Pointer to the map of the game
    Map* map;

    // Flags related to the status of the game
    bool finished_game;             // Whether the game is finished or not
    bool play_again;                // Whether the player wants to play again or not
    bool is_answered;               // Whether the player has answered the question at the end or not
    bool start_game;                // Whether the game has started or not
};


void is_game_finished();

// Globally available variable which is the only instance of the Game class
extern Game* GAME;
