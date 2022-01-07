#include <thread>
#include <mutex>
using namespace std;

#include "powerups.h"
#include "game.h"

// Constructor of a PowerUp (the only difference from a normal item is that powerups always blink in the map)
PowerUp::PowerUp(int x, int y, chtype c) : Item(x, y, true, true, c | A_BLINK) {}



// Constructor of an ExtraBomb powerup (represented by '@')
ExtraBomb::ExtraBomb(int x, int y) : PowerUp(x, y, '@') {}

// Function that is called when the item is picked up
void ExtraBomb::collide(Player *player) {
    
    // Increase the number of bombs the player can place
    player -> set_max_bombs(player -> get_max_bombs() + 1); 
    
    // Remove the item from the map
    GAME->map->clear_item(this); 
}



// Constructor of an ExtraRange powerup (represented by '$')
ExtraRange::ExtraRange(int x, int y) : PowerUp(x, y, '$') {}

// Function that is called when the item is picked up
void ExtraRange::collide(Player *player) {
    
    // Increase the range of the player's bombs
    player -> set_bomb_range(player -> get_bomb_range() + 1);

    // Remove the item from the map
    GAME->map->clear_item(this);
}