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
    srand(time(NULL));
    
    initscr();  
    noecho();
    setlocale(LC_ALL, "");
    curs_set(0);

    GAME = new Game();
    GAME -> start();
    
    endwin();
}
