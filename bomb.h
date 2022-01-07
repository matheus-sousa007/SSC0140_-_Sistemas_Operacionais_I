#pragma once

#include <mutex>
#include <thread>

#include "player.h"
#include "item.h"
using namespace std;

// Time to wait before a bomb explodes, in milliseconds
#define BOMB_LIFETIME 3000

// Duration of an explosion, in milliseconds
#define EXPLOSION_LIFETIME 1000

// Subclass of Item, which represents a bomb
class Bomb : public Item{
public:

    Bomb(int x, int y, int range, Player* player);

    // Controls the range of the bomb    
    void set_range(int range);
    int get_range();

    // Explodes the bomb (returns true if suceeded and false if the bomb has already exploded)
    bool explode();

    // Pointer to the player who placed the bomb
    Player *creator;

private:

    // Range of the bomb
    int range;

    // Whether the bomb has exploded or not
    bool exploded;

    // Thread and function that explodes the bomb after some time has passed
    thread countdown_thread;
    void countdown();
};



// Subclass of Item, which represents an explosion that is created in the map after a bomb explodes
class Explosion : public Item{
public:

    Explosion(int x, int y);

    // Kills a player whose position is within the explosion
    void collide(Player* player);

private:

    // Thread and function that removes the explosion after some time has passed
    thread countdown_thread;
    void countdown();

};