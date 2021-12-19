#include "item.h"
#include "player.h"

using namespace std;

class PowerUp : public Item {
    public: 
        PowerUp(int x, int y, chtype c);
        void collide(Player* player);
};

class ExtraRange: public PowerUp {
    public: 
        ExtraRange(int x, int y);
        void collide(Player* player);
};

class ExtraBomb: public PowerUp {
    public: 
        ExtraBomb(int x, int y);
        void collide(Player* player);
};