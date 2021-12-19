#pragma once
#include <mutex>
using namespace std;

class Player {
public:
    int max_bombs;
    int bomb_range;
    
    Player(int x, int y); 
    Player();  
    void move(int x, int y);
    void get_coordinates(int &x, int &y);
    
    int get_bombs_placed();
    void drop_bomb();
    void remove_bomb();

    int get_max_bombs();
    void set_max_bombs(int max_bombs);

    int get_bomb_range();
    void set_bomb_range(int bomb_range);

    bool is_alive();
    void kill();

private:
    int x;
    int y;
    bool alive;
    int bombs_placed;
    
    mutex *m;
};