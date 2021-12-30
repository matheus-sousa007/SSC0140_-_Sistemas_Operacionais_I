#pragma once

#include <vector>
#include <iostream>
using namespace std;

#include "player.h"
#include "map.h"
#include "bomb.h"

class Game{
public:
    Game();
    void intro_screen();
    void explanation_screen();
    void start();
    void loop();
    void end_of_game_screen();

    vector<Player*> players;
    Map* map;
    bool finished_game;
    bool play_again;
    bool is_answered;
    bool start_game;
};


void is_game_finished();
void new_game();

extern Game* GAME;
