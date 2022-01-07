#include <mutex>
#include <thread>

#include "map.h"
#include "game.h"

// Creates a map with the given width and height
Map::Map(int W, int H){
    this->W = W;
    this->H = H;

    this->m = new mutex();

    // Creates an empty 2D array of pointers to the items in the map
    items = new Item**[W];
    for (int i = 0; i < W; i++){
        items[i] = new Item*[H];
        for (int j = 0; j < H; j++) items[i][j] = NULL;
    }
}

// Returns the item at the given coordinates
Item* Map::get_item(int x, int y){

    // Checks if the coordinates are valid
    if (x < 0 || x >= W || y < 0 || y >= H)
        return NULL;
    
    m->lock();
    Item* item = items[x][y];
    m->unlock();

    return item;
}

// Adds the given item to the map
void Map::add_item(Item* item){

    // Gets the item's coordinates
    int x, y;
    item->get_coordinates(x, y);

    m->lock();
    items[x][y] = item;
    m->unlock();
}

// Removes the item at the given coordinates
void Map::clear_item(int x, int y){
    m->lock();
    items[x][y] = NULL;
    m->unlock();
}

// Removes the given item from the map
void Map::clear_item(Item* item){

    // Gets the item's coordinates
    int x, y;
    item->get_coordinates(x, y);
    
    m->lock();
    items[x][y] = NULL;
    m->unlock();
}

// Checks if the given coordinates are passable
bool Map::is_passable(int x, int y){
    bool passable = true;

    // Checks if there is an impassable item at the given coordinates
    Item* item = get_item(x, y);
    if (item != NULL) passable = item->is_passable();

    // Checks if there is a player at the given coordinates
    for (Player* player : GAME -> players){
        int px, py;
        player->get_coordinates(px, py);
        if (x == px && y == py) passable = false;
    }

    return passable;
}