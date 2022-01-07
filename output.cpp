#include <ncurses.h>
#include <thread>
#include <string>

#include "game.h"
#include "output.h"

void output_loop_fn(){
    while (GAME->play_again) {
        
        GAME->map->m->lock();        

        for (int x = 0; x < GAME -> map -> W; x++){
            for (int y = 0; y < GAME -> map -> H; y++){

                Item* item = GAME -> map -> items[x][y];

                if (item == NULL){
                    mvaddch(x, y, ' ');
                } else {
                    mvaddch(x, y,  item -> get_char());
                }
                
            }

        }

        for (Player* p : GAME -> players){
            if (!p -> is_alive())
                continue;
            
            int x, y;
            p -> get_coordinates(x, y);
            Item* item = GAME -> map -> items[x][y];
            if (item != NULL)
                mvaddch(x, y, 'P' | (A_REVERSE));
            else
                mvaddch(x, y, 'P');
        }
        GAME->map->m->unlock();
        refresh();
        // Sleeps for 1 second
        this_thread::sleep_for(chrono::milliseconds(33));
    }
    
}

