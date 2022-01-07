#pragma once

#include <thread>
#include <mutex>
using namespace std;

#include "item.h"

class Map{
public:

    Map(int W, int H);

    // Controls the placement of items in the map
    Item* get_item(int x, int y);
    void add_item(Item* item);
    void clear_item(int x, int y);
    void clear_item(Item* item);

    // Checks if the given coordinates are passable
    bool is_passable(int x, int y);

    // Height and width of the map
    int W, H;

    // 2D array of pointers to the items in the map
    Item*** items;

    // Mutex for the map
    mutex* m;
};