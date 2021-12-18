#pragma once
#include <ncurses.h>

using namespace std;

#include "player.h"

class Item{
public:
    Item(int x, int y, bool passable, bool destructible, chtype c);
    
    bool move(int dx, int dy);
    void get_coordinates(int &x, int &y);

    void set_passable(bool passable);
    bool is_passable();

    void set_destructible(bool destructible);
    bool is_destructible();

    virtual bool explode();
    
    virtual void collide(Player* player);

    chtype c;

protected:

    int x, y;
    
    bool passable;
    bool destructible;

    mutex* m;
};

class Wall : public Item {
    public: Wall(int x, int y);
};

class DestructibleWall : public Item {
    public: DestructibleWall(int x, int y);
};