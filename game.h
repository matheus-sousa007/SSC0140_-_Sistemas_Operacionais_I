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
    void start();
    void loop();
    
    vector<Player*> players;
    Map* map;
};

extern Game* GAME;