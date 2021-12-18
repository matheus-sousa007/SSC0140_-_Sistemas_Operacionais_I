#pragma once

#include <mutex>
#include <thread>

#include "player.h"
#include "item.h"
using namespace std;

class Bomb : public Item{
public:
    Bomb(int x, int y, int range, Player* player);
    
    void set_range(int range);
    int get_range();

    bool explode();

    thread countdown_thread;
    Player *creator;
private:

    int range;
    bool exploded;
    void countdown();

};


class Explosion : public Item{
public:
    Explosion(int x, int y);
    void collide(Player* player);
private:
    thread countdown_thread;
    void countdown();
};