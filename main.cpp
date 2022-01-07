#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <ncurses.h>
#include <time.h>

#include "game.h"

using namespace std;

Game* GAME;

int main(){

    // Creates the initial seed for the random number generator
    srand(time(NULL));
    
    // Initializes the ncurses library
    initscr();  
    noecho();
    setlocale(LC_ALL, "");
    curs_set(0);

    // Starts the game
    GAME = new Game();
    GAME -> start();
    
    // Closes the ncurses library
    endwin();
}
