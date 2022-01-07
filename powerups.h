#include "item.h"
#include "player.h"

using namespace std;

// Subclass of Item, which represents a generic powerup 
// (the only difference from a normal item is that powerups always blink in the map)
class PowerUp : public Item {
public: 
    PowerUp(int x, int y, chtype c);
};



// Subclass of PowerUp, which increases the range of a player's bombs
class ExtraRange: public PowerUp {
public: 

    ExtraRange(int x, int y);

    // Function that is called when the item is picked up
    void collide(Player* player);
};



// Subclass of PowerUp, which increases the number of bombs a player can place
class ExtraBomb: public PowerUp {
public: 

    ExtraBomb(int x, int y);

    // Function that is called when the item is picked up
    void collide(Player* player);
};