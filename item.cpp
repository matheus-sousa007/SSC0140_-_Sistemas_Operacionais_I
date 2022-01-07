#include <mutex>
#include <ncurses.h>

#include "game.h"
#include "item.h"
#include "powerups.h"

// Creates an item with the given coordinates, properties and appearance
Item::Item(int x, int y, bool passable, bool destructible, chtype c) {
    this->m = new mutex();
    m -> lock();
    this->x = x;
    this->y = y;
    this->passable = passable;
    this->destructible = destructible;
    this->c = c;
    m -> unlock();
}

// Moves the item by the given amounts
bool Item::move(int dx, int dy) {

    // Gets the item's coordinates
    int x, y;
    get_coordinates(x, y);
    
    // Calculates the new coordinates
    int new_x = x + dx;
    int new_y = y + dy;

    // Checks if the item can move to the new coordinates
    if (GAME -> map ->is_passable(new_x, new_y)) {

        // Update the item's coordinates
        this -> m -> lock();
        this->x = new_x;
        this->y = new_y;
        this -> m -> unlock();

        return true;
    }

    return false;
}

// Gets the item's coordinates
void Item::get_coordinates(int &x, int &y) {
    m->lock();
    x = this->x;
    y = this->y;
    m->unlock();
}

// Sets whether the item is passable or not
void Item::set_passable(bool passable) {
    m->lock();
    this->passable = passable;
    m->unlock();
}

// Checks if the item is passable or not
bool Item::is_passable() {
    m->lock();
    bool passable = this->passable;
    m->unlock();
    return passable;
}

// Sets whether the item is destructible or not
void Item::set_destructible(bool destructible) {
    m->lock();
    this->destructible = destructible;
    m->unlock();
}

// Checks if the item is destructible or not
bool Item::is_destructible() {
    m->lock();
    bool destructible = this->destructible;
    m->unlock();
    return destructible;
}

// Explodes an item, returning true if it is destructible and false otherwise 
bool Item::explode() {
    return is_destructible();
}

// Gets the item's appearance in the map
chtype Item::get_char() {
    chtype c;
    m->lock();
    c = this -> c;
    m->unlock();
    return c;
}

// Virtual method that must be implemented by the subclasses, which is called when a player passes over the item
void Item::collide(Player* player) {}



// Constructor of an indestructible wall
Wall::Wall(int x, int y) : Item(x, y, false, false, ' ' | A_REVERSE) {}



// Constructor of a destructible wall
DestructibleWall::DestructibleWall(int x, int y) : Item(x, y, false, true, '#') {}

// When a wall is destroyed, a powerup has a chance of being generated after the end of the explosion
bool DestructibleWall::explode() {
    this->countdown_thread = thread(&DestructibleWall::place_powerup, this);
    return true;
}

// Creates a powerup in the place of a wall that was destroyed
void DestructibleWall::place_powerup() {

    // Waits until the explosion ends
    this_thread::sleep_for(chrono::milliseconds(EXPLOSION_LIFETIME + 20));


    // Random PowerUp will appear 1/3 of the time
    if (rand() % 3) {

        // The random powerup can be either a ExtraBomb or ExtraRange
        int powerup_type = rand() % 2;

        switch (powerup_type){
        case 0:
            GAME -> map -> add_item(new ExtraRange(this->x, this->y));
            break;
        default:
            GAME -> map -> add_item(new ExtraBomb(this->x, this->y));
            break;
        }
    }}



// Constructor of a star item (purely cosmetic)
Star::Star(int x, int y) : Item(x, y, false, false, '*' | A_BOLD){}