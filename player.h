#pragma once
#include <mutex>
using namespace std;

class Player {
public:
    
    // Creates a player at the given coordinates
    Player(int x, int y);

    // Controls the position of the player
    void move(int dx, int dy);              // Moves the player by the given amounts
    void get_coordinates(int &x, int &y);   // Gets the player's coordinates
    
    // Controls the bombs placed by the player
    int get_bombs_placed();                 // Gets the number of bombs placed by the player
    void drop_bomb();                       // Drops a bomb at the player's current position
    void remove_bomb();                     // Signals that one of the player's bombs has been removed

    // Controls the maximum number of bombs the player can place
    int get_max_bombs();                
    void set_max_bombs(int max_bombs);

    // Controls the range of the player's bombs
    int get_bomb_range();
    void set_bomb_range(int bomb_range);

    // Controls whether the player is alive or not
    bool is_alive();
    void kill();

private:

    // Coordinates of the player
    int x, y;

    // Information about the player's bombs
    int max_bombs;                          // Number of bombs the player can place
    int bomb_range;                         // Range of the bombs
    int bombs_placed;                       // Number of bombs placed
    

    // Is the player alive?
    bool alive;             
    
    // Mutex for the player
    mutex *m;               

};