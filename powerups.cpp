#include <thread>
#include <mutex>
using namespace std;

#include "powerups.h"
#include "game.h"

PowerUp::PowerUp(int x, int y, chtype c) : Item(x, y, true, true, c | A_BLINK) {}
void PowerUp::collide(Player *player) {}

ExtraBomb::ExtraBomb(int x, int y) : PowerUp(x, y, '@') {

}
void ExtraBomb::collide(Player *player) {
    player -> max_bombs += 1;
    GAME->map->clear_item(this->x, this->y);
}

ExtraRange::ExtraRange(int x, int y) : PowerUp(x, y, '$') {}

void ExtraRange::collide(Player *player) {
    player -> bomb_range += 1;
    GAME->map->clear_item(this->x, this->y);
}