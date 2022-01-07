#include <thread>
#include <mutex>
using namespace std;

#include "bomb.h"
#include "game.h"

// Creates a bomb (represented by the blinking '+' character) which explodes after a certain amount of time
Bomb::Bomb(int x, int y, int range, Player* player) : Item(x, y, false, true, '+' | A_BLINK){
    this->m->lock();
    this->range = range;
    this->creator = player;
    this->exploded = false;
    this->m->unlock();
    
    // Creates a thread that will explode the bomb after a certain amount of time
    this->countdown_thread = thread(&Bomb::countdown, this); 
    
}

// Explodes the bomb after a certain amount of time
void Bomb::countdown(){
    this_thread::sleep_for(chrono::milliseconds(BOMB_LIFETIME));
    this->explode();
}

// Explodes the bomb
bool Bomb::explode(){       

    // Verifies if the bomb has already exploded, and if it hasn't, mark it as such
    this -> m -> lock();
    if (this->exploded){ 
        this -> m -> unlock();
        return false;
    }
    else this->exploded = true;
    this -> m -> unlock();

    // Removes a bomb from the corresponding player
    this->creator->remove_bomb();

    // Creates an explosion in the map in the same position as the bomb
    GAME -> map -> add_item(new Explosion(x, y));

    // Directional variables that indicate if each direction is free for the explosion
    bool up = true, down = true, left = true, right = true;

    // Creates an explosion in each direction up to the maximum range
    for (int i = 1; i <= range; i++){
        
        Item* item;

        // Verifies if the explosion can go down and if an item is there
        if (down){
            item = GAME -> map -> get_item(x + i, y);
            
            if (item){
                // If there is an item, it explodes
                down = item -> explode();       

                // It the item is not passable, the explosion stops in this direction
                if (!item -> is_passable()) down = false;
            }

            // If the item is destructible (or there is no item), it is destroyed and replaced by an explosion
            if (!item || item->is_destructible()) 
                GAME -> map -> add_item(new Explosion(x + i, y));     
        }

        // Verifies if the explosion can go up and if an item is there
        if (up){
            item = GAME -> map -> get_item(x - i, y);
            
            if (item){
                up = item -> explode();
                if (!item -> is_passable()) up = false;
            }

            if (!item || item->is_destructible()) 
                GAME -> map -> add_item(new Explosion(x - i, y));
        }

        // Verifies if the explosion can go left and if an item is there
        if (left){
            item = GAME -> map -> get_item(x, y - i);
            
            if (item){
                left = item -> explode();
                if (!item -> is_passable()) left = false;
            }

            if (!item || item->is_destructible()) 
                GAME -> map -> add_item(new Explosion(x, y - i));
        }

        // Verifies if the explosion can go right and if an item is there
        if (right){
            item = GAME -> map -> get_item(x, y + i);
            
            if (item){
                right = item -> explode();
                if (!item -> is_passable()) right = false;
            }

            if (!item || item->is_destructible()) 
                GAME -> map -> add_item(new Explosion(x, y + i));
        }

    }

    return true;
}



// Creates an explosion (represented by the '*' character) which damages any player that is in the same position
Explosion::Explosion(int x, int y)
    : Item(x, y, true, true, '*'){

    // Creates a thread that will remove the explosion after a certain amount of time
    this->countdown_thread = thread(&Explosion::countdown, this);
}

// Removes the explosion after a certain amount of time
void Explosion::countdown(){
    this_thread::sleep_for(chrono::milliseconds(EXPLOSION_LIFETIME));
    GAME -> map -> clear_item(this);
}

// Kills any player that is in the same position
void Explosion::collide(Player* player){
    player -> kill();
}