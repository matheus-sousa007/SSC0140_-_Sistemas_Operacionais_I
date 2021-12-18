#include "game.h"
#include "player.h"
#include "bomb.h"
#include <mutex>
using namespace std;

Player::Player(int x, int y) {
    this->x = x;
    this->y = y;
    this->bombs_placed = 0;
    this->bomb_range = 1;
    this->max_bombs = 1;
    this->alive = true;

    this->m = new mutex();
}

void Player::move(int dx, int dy) {
    if (!alive) return;
    
    int x, y;
    get_coordinates(x, y);
    
    int new_x = x + dx;
    int new_y = y + dy;

    if (GAME -> map ->is_passable(new_x, new_y)) {
        this -> m -> lock();
        this->x += dx;
        this->y += dy;
        this -> m -> unlock();
    }
    
}

// Gets the player's coordinates
void Player::get_coordinates(int &x, int &y) {
    this->m->lock();
    x = this->x;
    y = this->y;
    this->m->unlock();
}

int Player::get_bombs_placed() {
    this->m->lock();
    int bombs_placed = this->bombs_placed;
    this->m->unlock();
    return bombs_placed;
}

void Player::drop_bomb() {
    this->m->lock();
    if (alive){
        if (this->bombs_placed < this->max_bombs) {
            this->bombs_placed++;
            GAME -> map -> add_item(new Bomb(this->x, this->y, this->bomb_range, this));
        }
    }
    this->m->unlock();
}

void Player::remove_bomb() {
    this->m->lock();
    this->bombs_placed--;
    this->m->unlock();
}

bool Player::is_alive() {
    this->m->lock();
    bool alive = this->alive;
    this->m->unlock();
    return alive;
}

void Player::kill() {
    this->m->lock();
    this->alive = false;
    this->m->unlock();
}

int Player::get_max_bombs(){
    this->m->lock();
    int max_bombs = this->max_bombs;
    this->m->unlock();
    return max_bombs;
}

void Player::set_max_bombs(int max_bombs){
    this->m->lock();
    this->max_bombs = max_bombs;
    this->m->unlock();
}

int Player::get_bomb_range(){
    this->m->lock();
    int bomb_range = this->bomb_range;
    this->m->unlock();
    return bomb_range;
}
void Player::set_bomb_range(int bomb_range){
    this->m->lock();
    this->bomb_range = bomb_range;
    this->m->unlock();
}