#pragma once

#include <thread>
#include <mutex>
using namespace std;

#include "item.h"

class Map{
public:
    int W, H;

    Map(int W, int H);

    Item* get_item(int x, int y);
    void add_item(Item* item);
    void clear_item(int x, int y);

    bool is_passable(int x, int y);
private:
    Item*** items;
    mutex* m;
};