#include <ncurses.h>
#include <thread>
#include <string>

#include "game.h"
#include "output.h"

void output_loop_fn(){
    while (GAME->play_again) {
        for (int x = 0; x < GAME -> map -> W; x++){
            for (int y = 0; y < GAME -> map -> H; y++){

                Item* item = GAME -> map -> get_item(x, y);

                if (item == NULL){
                    mvaddch(x, y, ' ');
                } else {
                    int x, y;
                    item -> get_coordinates(x, y);
                    mvaddch(x, y, item -> c);
                }
                
            }

        }

        for (Player* p : GAME -> players){
            if (!p -> is_alive())
                continue;
            
            int x, y;
            p -> get_coordinates(x, y);
            Item* item = GAME -> map -> get_item(x, y);
            if (item != NULL)
                mvaddch(x, y, 'P' | (A_REVERSE));
            else
                mvaddch(x, y, 'P');
        }

        refresh();
        // Sleeps for 1 second
        this_thread::sleep_for(chrono::milliseconds(33));
    }
}

