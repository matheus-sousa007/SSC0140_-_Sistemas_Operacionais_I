#include <thread>
#include <iostream>
#include <ncurses.h>
#include <future>

#include "game.h"
#include "player.h"

void input_loop_fn(){
    while(!GAME->finished_game || GAME->play_again || !GAME->is_answered || !GAME->start_game){
        
        int input = getch();

        if(!GAME->start_game){
		if(input == '\n')
			GAME->start_game = true;
	}
	else if(!GAME->finished_game){
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
	else{
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
