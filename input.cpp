#include <thread>
#include <iostream>
#include <ncurses.h>

#include "game.h"
#include "player.h"

void input_loop_fn(){
    while(true){
        
        int input = getch();

        // if the user pressed an arrow key
        if (input == 27){
            getch();
            input = getch();
            switch(input){
                case 65:
                    GAME -> players[0] -> move(-1,0);
                    break;
                case 66:
                    GAME -> players[0] -> move(1,0);
                    break;
                case 67:
                    GAME -> players[0] -> move(0,1);
                    break;
                case 68:
                    GAME -> players[0] -> move(0,-1);
                    break;
            }
        } else{
            switch(input){
                case 'w':
                    GAME -> players[1] -> move(-1,0);
                    break;
                case 's':
                    GAME -> players[1] -> move(1,0);
                    break;
                case 'd':
                    GAME -> players[1] -> move(0,1);
                    break;
                case 'a':
                    GAME -> players[1] -> move(0,-1);
                    break;
                case 'e':
                    GAME -> players[1] -> drop_bomb();
                    break;
                case ' ':
                    GAME -> players[0] -> drop_bomb();
                    break;
            }
        }
    }
}
