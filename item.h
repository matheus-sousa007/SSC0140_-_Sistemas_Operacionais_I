#pragma once
#include <ncurses.h>
#include <thread>
using namespace std;

#include "player.h"

// Item class, which is the base class for all items in the game 
class Item{
public:
    
    Item(int x, int y, bool passable, bool destructible, chtype item_character);
    
    // Controls the position of the item
    bool move(int dx, int dy);              // Moves the item by the given amounts (returns true if the item moved)
    void get_coordinates(int &x, int &y);   // Gets the item's coordinates

    // Controls whether the item is passable or not
    void set_passable(bool passable);
    bool is_passable();

    // Controls whether the item is destructible or not
    void set_destructible(bool destructible);
    bool is_destructible();

    // Returns the character that represents the item
    chtype get_char();
    
    // Virtual function that is called when the item is exploded. Returns true if the item is destroyed and false otherwise
    virtual bool explode();
    
    // Virtual function that is called when the item is picked up
    virtual void collide(Player* player);

protected:

    // Character that represents the item in the map
    chtype c;

    // Coordinates of the item
    int x, y;
    
    // Is the item passable/destructible?
    bool passable;
    bool destructible;

    // Mutex for the item
    mutex* m;
};



// Subclass of Item, which represents an indestructible wall
class Wall : public Item {
    public: Wall(int x, int y);
};



// Subclass of Item, which represents a destructible wall
class DestructibleWall : public Item {
    public: 
        thread countdown_thread;
        DestructibleWall(int x, int y);
        bool explode();
        void place_powerup();
};



// Subclass of Item, which represents a star
class Star : public Item {
	public: Star(int x, int y);
};
