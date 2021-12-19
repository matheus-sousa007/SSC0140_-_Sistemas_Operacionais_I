#include <thread>
#include <mutex>
using namespace std;

#include "bomb.h"
#include "game.h"

#define BOMB_LIFETIME 3000

Bomb::Bomb(int x, int y, int range, Player* player) : Item(x, y, false, true, '+' | A_BLINK){

    this->range = range;
    this->creator = player;
    this->exploded = false;
    this->countdown_thread = thread(&Bomb::countdown, this);
}


void Bomb::countdown(){
    this_thread::sleep_for(chrono::milliseconds(BOMB_LIFETIME));
    this->explode();
}

bool Bomb::explode(){       

    this -> m -> lock();
    if (this->exploded) return false;
    else this->exploded = true;
    this -> m -> unlock();


    this->creator->remove_bomb();
    GAME -> map -> add_item(new Explosion(x, y));

    bool up = true, down = true, left = true, right = true;

    for (int i = 0; i <= range; i++){
        if (i == 0)
            continue;

        Item* item;

        if ((item = GAME -> map -> get_item(x + i, y)) && down)
            down = item -> explode();
        if (down) GAME -> map -> add_item(new Explosion(x + i, y));
    
        
        if ((item = GAME -> map -> get_item(x - i, y)) && up)
            up = item -> explode();
        if (up) GAME -> map -> add_item(new Explosion(x - i, y));
        

        if ((item = GAME -> map -> get_item(x, y + i)) && right)
            right = item -> explode();
        if (right) GAME -> map -> add_item(new Explosion(x, y + i));
        

        if ((item = GAME -> map -> get_item(x, y - i)) && left)
            left = item -> explode();
        if (left) GAME -> map -> add_item(new Explosion(x, y - i));
            
    }

    return true;
}

Explosion::Explosion(int x, int y)
    : Item(x, y, true, true, '*'){
    this->countdown_thread = thread(&Explosion::countdown, this);
}

void Explosion::countdown(){
    this_thread::sleep_for(chrono::milliseconds(EXPLOSION_LIFETIME));
    GAME -> map -> clear_item(this->x, this->y);
}

void Explosion::collide(Player* player){
    player -> kill();
}