#include <thread>
#include <math.h>
#include <ncurses.h>    
#include <algorithm>
#include <future>
#include <bits/stdc++.h>

using namespace std;

#include "game.h"
#include "input.h"
#include "output.h"
#include "player.h"
#include "bomb.h"
#include "map.h"

#define MAP_HEIGHT 25
#define MAP_WIDTH 55

#define LETTER_DELAY 15

Game::Game(){
    this -> map = new Map(MAP_HEIGHT, MAP_WIDTH);
} 

void Game::intro_screen(){

    // B
    //cout << "MAP_HEIGHT = " << map->H << " MAP_WIDTH = " << map->W << endl;
    for(int i = map->W/2 - 2; i < map->W/2 + 3; i++){
        map->add_item(new Wall(i, 1));
        map->add_item(new Wall(i, 6));
        map->add_item(new Wall(i, 9));
        map->add_item(new Wall(i, 11));
        map->add_item(new Wall(i, 15));
        map->add_item(new Wall(i, 17));
        map->add_item(new Wall(i, 22));
        map->add_item(new Wall(i, 27));
        map->add_item(new Wall(i, 32));
        map->add_item(new Wall(i, 36));
        map->add_item(new Wall(i, 48));
        map->add_item(new Wall(i, 52));
    }
    
    map->add_item(new Wall(map->W/2 - 2, 2));
    map->add_item(new Wall(map->W/2, 2));
    map->add_item(new Wall(map->W/2 + 2, 2));
    map->add_item(new Wall(map->W/2 - 2, 3));
    map->add_item(new Wall(map->W/2, 3));
    map->add_item(new Wall(map->W/2 + 2, 3));
    map->add_item(new Wall(map->W/2 - 1, 4));
    map->add_item(new Wall(map->W/2 + 1, 4));
    // O
    map->add_item(new Wall(map->W/2 - 2, 7));
    map->add_item(new Wall(map->W/2 + 2, 7));
    map->add_item(new Wall(map->W/2 - 2, 8));
    map->add_item(new Wall(map->W/2 + 2, 8));
    // M
    map->add_item(new Wall(map->W/2 - 1, 12));
    map->add_item(new Wall(map->W/2, 13));
    map->add_item(new Wall(map->W/2 - 1, 14));
    // B
    map->add_item(new Wall(map->W/2 - 2, 18));
    map->add_item(new Wall(map->W/2, 18));
    map->add_item(new Wall(map->W/2 + 2, 18));
    map->add_item(new Wall(map->W/2 - 2, 19));
    map->add_item(new Wall(map->W/2, 19));
    map->add_item(new Wall(map->W/2 + 2, 19));
    map->add_item(new Wall(map->W/2 - 1, 20));
    map->add_item(new Wall(map->W/2 + 1, 20));
    // E 
    map->add_item(new Wall(map->W/2 - 2, 23));
    map->add_item(new Wall(map->W/2, 23));
    map->add_item(new Wall(map->W/2 + 2, 23));
    map->add_item(new Wall(map->W/2 - 2, 24));
    map->add_item(new Wall(map->W/2, 24));
    map->add_item(new Wall(map->W/2 + 2, 24));
    map->add_item(new Wall(map->W/2 - 2, 25));
    map->add_item(new Wall(map->W/2, 25));
    map->add_item(new Wall(map->W/2 + 2, 25));
    // R 
    map->add_item(new Wall(map->W/2 - 2, 28));
    map->add_item(new Wall(map->W/2, 28));
    map->add_item(new Wall(map->W/2 - 2, 29));
    map->add_item(new Wall(map->W/2, 29));
    map->add_item(new Wall(map->W/2 - 1, 30));
    map->add_item(new Wall(map->W/2 + 1, 29));
    map->add_item(new Wall(map->W/2 + 2, 30));
    // M 
    map->add_item(new Wall(map->W/2 - 1, 33));
    map->add_item(new Wall(map->W/2, 34));
    map->add_item(new Wall(map->W/2 - 1, 35));
    // A
    map->add_item(new Wall(map->W/2 - 2, 42));
    map->add_item(new Wall(map->W/2 - 1, 41));
    map->add_item(new Wall(map->W/2 - 1, 43));
    map->add_item(new Wall(map->W/2, 40));
    map->add_item(new Wall(map->W/2, 44));
    for(int i = 39; i < 46; i++){
        map->add_item(new Wall(map->W/2 + 1, i));
    }
    map->add_item(new Wall(map->W/2 + 2, 38));
    map->add_item(new Wall(map->W/2 + 2, 46));
    // N
    map->add_item(new Wall(map->W/2 - 1, 49));
    map->add_item(new Wall(map->W/2, 50));
    map->add_item(new Wall(map->W/2 + 1, 51));


    // Put star in intro_screen
    for(int i = 0; i < map->W/2 - 2; i++){
        map->add_item(new Item(i, i+2, false, false, '*' | A_BOLD));
        map->add_item(new Item(i, map->H/2, false, false, '*' | A_BOLD));
        map->add_item(new Item(i, map->H - i - 2, false, false, '*' | A_BOLD));
    }

    for(int i = map->W/2 + 3; i < map->W; i++){
        map->add_item(new Item(i, i + map->H/2, false, false, '*' | A_BOLD));
        map->add_item(new Item(i, map->H/2, false, false, '*' | A_BOLD));
        map->add_item(new Item(i, map->H/2 - i, false, false, '*' | A_BOLD));
    }

    this_thread::sleep_for(chrono::milliseconds(1000));

    // clear map

    for(int i = 0; i < map->W; i++){
        for(int j = 0; j < map->H; j++){
            map->clear_item(i, j);
        }
    }
}

void Game::explanation_screen(){

    // Construct the explanation screen
    //S
    map->add_item(new Wall(3,12));
    map->add_item(new Wall(3,13));
    map->add_item(new Wall(3,14));
    map->add_item(new Wall(4,12));
    map->add_item(new Wall(5,12));
    map->add_item(new Wall(5,13));
    map->add_item(new Wall(5,14));
    map->add_item(new Wall(6,14));
    map->add_item(new Wall(7,12));
    map->add_item(new Wall(7,13));
    map->add_item(new Wall(7,14));
    //Y
    map->add_item(new Wall(3,16));
    map->add_item(new Wall(4,17));
    map->add_item(new Wall(5,18));
    map->add_item(new Wall(4,19));
    map->add_item(new Wall(3,20));
    map->add_item(new Wall(6,18));
    map->add_item(new Wall(7,18));
    //M
    for(int i = 3; i < 8; i++){
        map->add_item(new Wall(i,21));
        map->add_item(new Wall(i,25));
        map->add_item(new Wall(i,27));
        map->add_item(new Wall(i,32));
        map->add_item(new Wall(i,35));
        map->add_item(new Wall(i,37));
    }
    map->add_item(new Wall(4,22));
    map->add_item(new Wall(5,23));
    map->add_item(new Wall(4,24));
    //B
    map->add_item(new Wall(3,28));
    map->add_item(new Wall(3,29));
    map->add_item(new Wall(5,28));
    map->add_item(new Wall(5,29));
    map->add_item(new Wall(7,28));
    map->add_item(new Wall(7,29));
    map->add_item(new Wall(4,30));
    map->add_item(new Wall(6,30));
    //O
    map->add_item(new Wall(3,33));
    map->add_item(new Wall(3,34));
    map->add_item(new Wall(7,33));
    map->add_item(new Wall(7,34));
    //L
    map->add_item(new Wall(7,38));
    map->add_item(new Wall(7,39));
    map->add_item(new Wall(7,40));
    //S
    map->add_item(new Wall(3,42));
    map->add_item(new Wall(3,43));
    map->add_item(new Wall(3,44));
    map->add_item(new Wall(4,42));
    map->add_item(new Wall(5,42));
    map->add_item(new Wall(5,43));
    map->add_item(new Wall(5,44));
    map->add_item(new Wall(6,44));
    map->add_item(new Wall(7,42));
    map->add_item(new Wall(7,43));
    map->add_item(new Wall(7,44));

    // explaining symbols:

    // + -> Player's bomb

    map->add_item(new Item(10, 8, false, false, '+' | A_BOLD));
    map->add_item(new Item(10, 10, false, false, '-' | A_BOLD));
    map->add_item(new Item(10, 11, false, false, '>' | A_BOLD));
    map->add_item(new Item(10, 13, false, false, 'P' | A_BOLD));
    map->add_item(new Item(10, 14, false, false, 'l' | A_BOLD));
    map->add_item(new Item(10, 15, false, false, 'a' | A_BOLD));
    map->add_item(new Item(10, 16, false, false, 'y' | A_BOLD));
    map->add_item(new Item(10, 17, false, false, 'e' | A_BOLD));
    map->add_item(new Item(10, 18, false, false, 'r' | A_BOLD));
    map->add_item(new Item(10, 19, false, false, '\'' | A_BOLD));
    map->add_item(new Item(10, 20, false, false, 's' | A_BOLD));
    map->add_item(new Item(10, 22, false, false, 'B' | A_BOLD));
    map->add_item(new Item(10, 23, false, false, 'o' | A_BOLD));
    map->add_item(new Item(10, 24, false, false, 'm' | A_BOLD));
    map->add_item(new Item(10, 25, false, false, 'b' | A_BOLD));

    // # -> Destructible Wall
    map->add_item(new Item(12, 8, false, false, '#' | A_BOLD));
    map->add_item(new Item(12, 10, false, false, '-' | A_BOLD));
    map->add_item(new Item(12, 11, false, false, '>' | A_BOLD));
    map->add_item(new Item(12, 13, false, false, 'D' | A_BOLD));
    map->add_item(new Item(12, 14, false, false, 'e' | A_BOLD));
    map->add_item(new Item(12, 15, false, false, 's' | A_BOLD));
    map->add_item(new Item(12, 16, false, false, 't' | A_BOLD));
    map->add_item(new Item(12, 17, false, false, 'r' | A_BOLD));
    map->add_item(new Item(12, 18, false, false, 'u' | A_BOLD));
    map->add_item(new Item(12, 19, false, false, 't' | A_BOLD));
    map->add_item(new Item(12, 20, false, false, 'i' | A_BOLD));
    map->add_item(new Item(12, 21, false, false, 'b' | A_BOLD));
    map->add_item(new Item(12, 22, false, false, 'l' | A_BOLD));
    map->add_item(new Item(12, 23, false, false, 'e' | A_BOLD));
    map->add_item(new Item(12, 25, false, false, 'W' | A_BOLD));
    map->add_item(new Item(12, 26, false, false, 'a' | A_BOLD));
    map->add_item(new Item(12, 27, false, false, 'l' | A_BOLD));
    map->add_item(new Item(12, 28, false, false, 'l' | A_BOLD));


    // @ -> Increase bomb range


    map->add_item(new Item(14, 8, false, false, '$' | A_BOLD));
    map->add_item(new Item(14, 10, false, false, '-' | A_BOLD));
    map->add_item(new Item(14, 11, false, false, '>' | A_BOLD));
    map->add_item(new Item(14, 13, false, false, 'I' | A_BOLD));
    map->add_item(new Item(14, 14, false, false, 'n' | A_BOLD));
    map->add_item(new Item(14, 15, false, false, 'c' | A_BOLD));
    map->add_item(new Item(14, 16, false, false, 'r' | A_BOLD));
    map->add_item(new Item(14, 17, false, false, 'e' | A_BOLD));
    map->add_item(new Item(14, 18, false, false, 'a' | A_BOLD));
    map->add_item(new Item(14, 19, false, false, 's' | A_BOLD));
    map->add_item(new Item(14, 20, false, false, 'e' | A_BOLD));
    map->add_item(new Item(14, 22, false, false, 'B' | A_BOLD));
    map->add_item(new Item(14, 23, false, false, 'o' | A_BOLD));
    map->add_item(new Item(14, 24, false, false, 'm' | A_BOLD));
    map->add_item(new Item(14, 25, false, false, 'b' | A_BOLD));
    map->add_item(new Item(14, 27, false, false, 'R' | A_BOLD));
    map->add_item(new Item(14, 28, false, false, 'a' | A_BOLD));
    map->add_item(new Item(14, 29, false, false, 'n' | A_BOLD));
    map->add_item(new Item(14, 30, false, false, 'g' | A_BOLD));
    map->add_item(new Item(14, 31, false, false, 'e' | A_BOLD));

    // $ -> Increase max bombs

    map->add_item(new Item(16, 8, false, false, '@' | A_BOLD));
    map->add_item(new Item(16, 10, false, false, '-' | A_BOLD));
    map->add_item(new Item(16, 11, false, false, '>' | A_BOLD));
    map->add_item(new Item(16, 13, false, false, 'I' | A_BOLD));
    map->add_item(new Item(16, 14, false, false, 'n' | A_BOLD));
    map->add_item(new Item(16, 15, false, false, 'c' | A_BOLD));
    map->add_item(new Item(16, 16, false, false, 'r' | A_BOLD));
    map->add_item(new Item(16, 17, false, false, 'e' | A_BOLD));
    map->add_item(new Item(16, 18, false, false, 'a' | A_BOLD));
    map->add_item(new Item(16, 19, false, false, 's' | A_BOLD));
    map->add_item(new Item(16, 20, false, false, 'e' | A_BOLD));
    map->add_item(new Item(16, 22, false, false, 'm' | A_BOLD));
    map->add_item(new Item(16, 23, false, false, 'a' | A_BOLD));
    map->add_item(new Item(16, 24, false, false, 'x' | A_BOLD));
    map->add_item(new Item(16, 26, false, false, 'n' | A_BOLD));
    map->add_item(new Item(16, 27, false, false, 'u' | A_BOLD));
    map->add_item(new Item(16, 28, false, false, 'm' | A_BOLD));
    map->add_item(new Item(16, 29, false, false, 'b' | A_BOLD));
    map->add_item(new Item(16, 30, false, false, 'e' | A_BOLD));
    map->add_item(new Item(16, 31, false, false, 'r' | A_BOLD));
    map->add_item(new Item(16, 33, false, false, 'o' | A_BOLD));
    map->add_item(new Item(16, 34, false, false, 'f' | A_BOLD));
    map->add_item(new Item(16, 36, false, false, 'b' | A_BOLD));
    map->add_item(new Item(16, 37, false, false, 'o' | A_BOLD));
    map->add_item(new Item(16, 38, false, false, 'm' | A_BOLD));
    map->add_item(new Item(16, 39, false, false, 'b' | A_BOLD));
    map->add_item(new Item(16, 40, false, false, 's' | A_BOLD));

    this_thread::sleep_for(chrono::milliseconds(500));

    // pressione ENTER para continuar
    map->add_item(new Item(map->W -2, 9, false, false, 'p' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 10, false, false, 'r' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 11, false, false, 'e' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 12, false, false, 's' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 13, false, false, 's' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 14, false, false, 'i' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 15, false, false, 'o' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 16, false, false, 'n' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 17, false, false, 'e' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 19, false, false, 'E' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 20, false, false, 'N' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 21, false, false, 'T' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 22, false, false, 'E' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 23, false, false, 'R' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 25, false, false, 'p' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 26, false, false, 'a' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 27, false, false, 'r' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 28, false, false, 'a' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 30, false, false, 'c' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 31, false, false, 'o' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 32, false, false, 'n' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 33, false, false, 't' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 34, false, false, 'i' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 35, false, false, 'n' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 36, false, false, 'u' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 37, false, false, 'a' | A_BOLD));
    this_thread::sleep_for(chrono::milliseconds(LETTER_DELAY));
    map->add_item(new Item(map->W -2, 38, false, false, 'r' | A_BOLD));



    cout << "We got until here" << endl;
    while(!this->start_game);	

        // clear map
        for(int i = 0; i < map->W; i++){
            for(int j = 0; j < map->H; j++)
                map->clear_item(i,j);
    }
}


void Game::start(){
    this->play_again = true;
    this->is_answered = false;
    this->start_game = false;

    thread input_thread(&input_loop_fn);
    thread output_thread(&output_loop_fn);

    while(this->play_again){
        this->is_answered = false;
        this->finished_game = false;
        this->intro_screen();
        if(!this->start_game) this->explanation_screen();

        for (int i = 1; i < this -> map -> W - 1; i++){
            map -> add_item(new Wall(i,0));
            map -> add_item(new Wall(i,map -> H - 1));

            for (int j = 1; j < this -> map -> H - 1; j++){
                if ((j % 2 == 0) && (i % 2 == 0))
                    map -> add_item(new Wall(i,j));
            }
        }

        for (int i = 0; i < this -> map -> H; i++){
            map -> add_item(new Wall(0,i));
            map -> add_item(new Wall(map -> W - 1,i));
        }

        for (int i = 1; i < this -> map -> W - 1; i++) {
            for (int j = 1; j < this -> map -> H - 1; j++) {
                if (map->get_item(i, j) == NULL && !(rand() % 3))
                    map -> add_item(new DestructibleWall(i, j));
            }
        }

        // Making room for players to start
        map->clear_item(1, 2);
        map->clear_item(1, 1);
        map->clear_item(2, 1);
        players.push_back(new Player(1, 1));

        map->clear_item(map->W - 2, map->H - 3);
        map->clear_item(map->W - 2, map->H - 2);
        map->clear_item(map->W - 3, map->H - 2);
        players.push_back(new Player(map->W - 2,map-> H - 2));

        this->play_again = true;

        thread finished(&is_game_finished);

        while (!this->finished_game){
            this -> loop();
        }


        this_thread::sleep_for(chrono::milliseconds(EXPLOSION_LIFETIME + 1000));


        // Limpa o mapa 
        for(int i = 0; i < MAP_HEIGHT; i++){
            for(int j = 0; j < MAP_WIDTH; j++){
                map->clear_item(i,j);
            }
        }

        players.clear();


        finished.join();

        this->end_of_game_screen();	    
    }
    input_thread.join();
    output_thread.join();
}

void Game::loop(){
    for (int i = 0; i < players.size(); i++){
        int x, y;
        players[i] -> get_coordinates(x, y);
        Item* item = map -> get_item(x, y);
        if (item != NULL){
            item -> collide(players[i]);
        }
    }
}

void Game::end_of_game_screen(){

    this_thread::sleep_for(chrono::milliseconds(EXPLOSION_LIFETIME));

    // Construir a tela de ganhador	

    // F
    for(int i = 3; i < 8; i++){
        map->add_item(new Wall(i, 18));
        map->add_item(new Wall(i, 25));
        map->add_item(new Wall(i, 27));
        map->add_item(new Wall(i, 33));
    }
    for(int j = 19; j < 23; j++){
        map->add_item(new Wall(3, j));
        map->add_item(new Wall(6, j));
    }

    // I
    map->add_item(new Wall(1, 25));
    // M
    map->add_item(new Wall(4,28));
    map->add_item(new Wall(5,29));
    map->add_item(new Wall(6,30));
    map->add_item(new Wall(5,31));
    map->add_item(new Wall(4,32));
    // D
    for(int i = 10; i < 15; i++){
    map->add_item(new Wall(i, 21));
    }
    map->add_item(new Wall(10,22));
    map->add_item(new Wall(11,23));
    map->add_item(new Wall(12,24));
    map->add_item(new Wall(13,23));
    map->add_item(new Wall(14,22));
    // E
    for(int i = 10; i < 15; i++){
        map->add_item(new Wall(i, 26));
    }

    for(int i = 27; i < 31; i++){
        map->add_item(new Wall(10, i));
        map->add_item(new Wall(12, i));
        map->add_item(new Wall(14, i));
    }

    // J
    map->add_item(new Wall(17, 14));
    map->add_item(new Wall(17, 15));
    map->add_item(new Wall(17, 16));
    map->add_item(new Wall(17, 17));
    map->add_item(new Wall(17, 18));
    for(int i = 17; i < 23; i++){
        map->add_item(new Wall(i, 16));
    }
    map->add_item(new Wall(22, 15));
    map->add_item(new Wall(22, 14));
    map->add_item(new Wall(21, 14));
    // O
    for(int i = 17; i < 23; i++){
    map->add_item(new Wall(i, 20));
    map->add_item(new Wall(i, 23));
    }
    map->add_item(new Wall(17, 21));
    map->add_item(new Wall(22, 21));
    map->add_item(new Wall(17, 22));
    map->add_item(new Wall(22, 22));
    // G
    for(int i = 17; i < 23; i++){
        map->add_item(new Wall(i, 25));
    }
    map->add_item(new Wall(17, 26));
    map->add_item(new Wall(17, 27));
    map->add_item(new Wall(17, 28));
    map->add_item(new Wall(22, 26));
    map->add_item(new Wall(22, 27));
    map->add_item(new Wall(22, 28));
    map->add_item(new Wall(21, 28));
    map->add_item(new Wall(20, 28));
    map->add_item(new Wall(20, 27));
    map->add_item(new Wall(20, 29));
    map->add_item(new Wall(20, 30));
    map->add_item(new Wall(21, 30));
    // O
    for(int i = 17; i < 23; i++){
        map->add_item(new Wall(i, 32));
        map->add_item(new Wall(i, 35));
    }
    map->add_item(new Wall(17, 33));
    map->add_item(new Wall(22, 33));
    map->add_item(new Wall(17, 34));
    map->add_item(new Wall(22, 34));


    for(int i = 0; i < MAP_HEIGHT; i++){
        map->add_item(new Star(i, 0));
        map->add_item(new Star(i, MAP_WIDTH - 1));
    } 
    for(int i = 0; i < MAP_WIDTH-1; i++){
        map->add_item(new Star(0, i));
        map->add_item(new Star(MAP_HEIGHT-1, i));
    }

    // Jogar novamente
    map->add_item(new Item(MAP_HEIGHT-2, 8, false, false, 'J' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 9, false, false, 'O' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 10, false, false, 'G' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 11, false, false, 'A' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 12, false, false, 'R' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 14, false, false, 'N' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 15, false, false, 'O' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 16, false, false, 'V' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 17, false, false, 'A' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 18, false, false, 'M' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 19, false, false, 'E' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 20, false, false, 'N' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 21, false, false, 'T' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 22, false, false, 'E' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 23, false, false, '?' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 25, false, false, '(' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 26, false, false, 'E' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 27, false, false, 'N' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 28, false, false, 'T' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 29, false, false, 'E' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 30, false, false, 'R' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 31, false, false, ')' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 33, false, false, 'S' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 34, false, false, 'i' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 35, false, false, 'm' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 37, false, false, '(' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 38, false, false, 'Q' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 39, false, false, ')' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 41, false, false, 'N' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 42, false, false, 'a' | A_BOLD));
    map->add_item(new Item(MAP_HEIGHT-2, 43, false, false, 'o' | A_BOLD));


    // Delay
    while(!this->is_answered);

        // Apagar a tela
        for(int i = 0; i < map->W; i++){
            for(int j = 0; j < map->H; j++)
                map->clear_item(i,j);
    }
}

void is_game_finished(){
    while(!GAME->finished_game){
        if(count_if(GAME->players.begin(), GAME->players.end(), [](Player* p){return p->is_alive();}) == 1) GAME->finished_game = true;
    }
}
