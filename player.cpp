#include "game.h"
#include "player.h"
#include "bomb.h"
#include <mutex>
using namespace std;

// Creates a player at the given coordinates
Player::Player(int x, int y) {
    this->m = new mutex();
    m -> lock();
    this->x = x;
    this->y = y;
    this->bombs_placed = 0;
    this->bomb_range = 1;
    this->max_bombs = 1;
    this->alive = true;
    m -> unlock();
}

// Moves the item by the given amounts
void Player::move(int dx, int dy) {

    // Returns if the player is dead
    if (!this -> is_alive()) return;
    
    // Gets the player's coordinates
    int x, y;
    get_coordinates(x, y);
    
    // Calculates the new coordinates
    int new_x = x + dx;
    int new_y = y + dy;

    // Checks if the player can move to the new coordinates
    if (GAME -> map ->is_passable(new_x, new_y)) {

        // Update the player's coordinates
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

// Gets the number of bombs placed by the player
int Player::get_bombs_placed() {
    this->m->lock();
    int bombs_placed = this->bombs_placed;
    this->m->unlock();
    return bombs_placed;
}

// Drops a bomb at the player's current position
void Player::drop_bomb() {

    // Returns if the player is dead
    if (!this -> is_alive()) return;

    m -> lock();

    // Checks if the player can place a bomb
    if (this->bombs_placed < this->max_bombs) {

        // Creates a bomb at the player's current position
        GAME -> map -> add_item(new Bomb(this->x, this->y, this->bomb_range, this));
        this->bombs_placed++;

    }

    m -> unlock();

}

// Signals that one of the player's bombs has been removed
void Player::remove_bomb() {
    this->m->lock();
    this->bombs_placed--;
    this->m->unlock();
}

// Returns whether the player is alive or not
bool Player::is_alive() {
    this->m->lock();
    bool alive = this->alive;
    this->m->unlock();
    return alive;
}

// Kills the player
void Player::kill() {
    this->m->lock();
    this->alive = false;
    this->m->unlock();
}

// Gets the maximum number of bombs the player can place
int Player::get_max_bombs(){
    this->m->lock();
    int max_bombs = this->max_bombs;
    this->m->unlock();
    return max_bombs;
}

// Sets the maximum number of bombs the player can place
void Player::set_max_bombs(int max_bombs){
    this->m->lock();
    this->max_bombs = max_bombs;
    this->m->unlock();
}

// Gets the range of the player's bombs
int Player::get_bomb_range(){
    this->m->lock();
    int bomb_range = this->bomb_range;
    this->m->unlock();
    return bomb_range;
}

// Sets the range of the player's bombs
void Player::set_bomb_range(int bomb_range){
    this->m->lock();
    this->bomb_range = bomb_range;
    this->m->unlock();
}