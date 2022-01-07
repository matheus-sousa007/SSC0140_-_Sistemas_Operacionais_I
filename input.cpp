#include <thread>
#include <iostream>
#include <ncurses.h>
#include <future>

#include "game.h"
#include "player.h"

// Thread which controls the game's keyboard inputs
void input_loop_fn(){

    // Repeats while the game has not ended
    while(!GAME->finished_game || GAME->play_again || !GAME->is_answered || !GAME->start_game){
        
        // Gets the input from the user
        int input = getch();

        // If the game hasn't started yet, the user start the game by pressing ENTER
        if(!GAME->start_game){
		    if(input == '\n')
			    GAME->start_game = true;
	    
        
        // If the game is running, the keyboard controls the players
	    }else if(!GAME->finished_game){

            // Checks if the user pressed any directional key, and moves player 1 accordingly
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

            } else {

                switch(input){
                    // Moves player 2 with WASD
                    case 'W':
                    case 'w':
                        GAME -> players[1] -> move(-1,0);
                        break;
                    case 'S':
                    case 's':
                        GAME -> players[1] -> move(1,0);
                        break;
                    case 'D':
                    case 'd':
                        GAME -> players[1] -> move(0,1);
                        break;
                    case 'A':
                    case 'a':
                        GAME -> players[1] -> move(0,-1);
                        break;

                    // Player 2 places a bomb on the 'e' key
                    case 'E':
                    case 'e':
                        GAME -> players[1] -> drop_bomb();
                        break;

                    // Player 1 places a bomb on the SPACEBAR key
                    case ' ':
                        GAME -> players[0] -> drop_bomb();
                        break;
                }
            }

        // If the game is finished, the user can play again by pressing ENTER, or quit by pressing 'q'
        }else{
            switch(input){
                case '\n':
                    GAME->play_again = true;
                    GAME->is_answered = true;
                    break;
                case 'q':
                case 'Q':
                    GAME->play_again = false;
                    GAME->is_answered = true;
                    break;

            }
        }
    }
}
