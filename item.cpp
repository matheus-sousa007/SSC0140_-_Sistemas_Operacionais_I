#include <mutex>
#include <ncurses.h>

#include "game.h"
#include "item.h"
#include "powerups.h"

Item::Item(int x, int y, bool passable, bool destructible, chtype c) {
    this->x = x;
    this->y = y;
    this->passable = passable;
    this->destructible = destructible;
    this->c = c;
    this->m = new mutex();
}

bool Item::move(int dx, int dy) {
    bool moved = false;

    int x, y;
    get_coordinates(x, y);
    
    int new_x = x + dx;
    int new_y = y + dy;

    if (GAME -> map ->is_passable(new_x, new_y)) {
        this -> m -> lock();
        this->x += dx;
        this->y += dy;
        moved = true;
        this -> m -> unlock();
    }
    return moved;
}

void Item::get_coordinates(int &x, int &y) {
    m->lock();
    x = this->x;
    y = this->y;
    m->unlock();
}

void Item::set_passable(bool passable) {
    m->lock();
    this->passable = passable;
    m->unlock();
}

bool Item::is_passable() {
    m->lock();
    bool passable = this->passable;
    m->unlock();
    return passable;
}

void Item::set_destructible(bool destructible) {
    m->lock();
    this->destructible = destructible;
    m->unlock();
}

bool Item::is_destructible() {
    m->lock();
    bool destructible = this->destructible;
    m->unlock();
    return destructible;
}

bool Item::explode() {
    return is_destructible();
}

// Método virtual que deve ser implementado pelas classes derivadas
void Item::collide(Player* player) {
}


Wall::Wall(int x, int y) : Item(x, y, false, false, ' ' | A_REVERSE) {}

DestructibleWall::DestructibleWall(int x, int y) : Item(x, y, false, true, '#') {
}

bool DestructibleWall::explode() {
    this->countdown_thread = thread(&DestructibleWall::place_powerup, this);
    return is_destructible();
}

void DestructibleWall::place_powerup() {
    this_thread::sleep_for(chrono::milliseconds(EXPLOSION_LIFETIME + 20));
    // Random PowerUp will appear 1/3 of the time
    if (rand() % 3) {
        // The random powerup can be either a ExtraBomb or ExtraRange
        int powerup_type = rand() % 2;

        switch (powerup_type)
        {
        case 0:
            GAME -> map -> add_item(new ExtraRange(this->x, this->y));
            break;
        default:
            GAME -> map -> add_item(new ExtraBomb(this->x, this->y));
            break;
        }
    }}

Star::Star(int x, int y) : Item(x, y, false, false, '*' | A_BOLD){}
