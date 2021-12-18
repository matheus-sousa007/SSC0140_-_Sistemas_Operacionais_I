#include <mutex>
#include <thread>

#include "map.h"
#include "game.h"

Map::Map(int W, int H){
    this->W = W;
    this->H = H;
    this->m = new mutex();

    items = new Item**[W];
    for (int i = 0; i < W; i++){
        items[i] = new Item*[H];
        for (int j = 0; j < H; j++) items[i][j] = NULL;
    }

}

Item* Map::get_item(int x, int y){
    if (x < 0 || x >= W || y < 0 || y >= H)
        return NULL;
    
    m->lock();
    Item* item = items[x][y];
    m->unlock();
    return item;
}

void Map::add_item(Item* item){
    m->lock();
    int x, y;
    item->get_coordinates(x, y);
    items[x][y] = item;
    m->unlock();
}

void Map::clear_item(int x, int y){
    m->lock();
    items[x][y] = NULL;
    m->unlock();
}

bool Map::is_passable(int x, int y){
    m->lock();
    bool passable = true;
    if (items[x][y] != NULL) passable = items[x][y]->is_passable();

    for (Player* player : GAME -> players){
        int px, py;
        player->get_coordinates(px, py);
        if (x == px && y == py) passable = false;
    }

    m->unlock();
    return passable;
}