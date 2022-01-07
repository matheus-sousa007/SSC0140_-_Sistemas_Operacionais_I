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

// Creates the empty game map
Game::Game(){
    this->map = new Map(MAP_HEIGHT, MAP_WIDTH);
}

// Starts the game
void Game::start(){

    // Sets up initial variables
    this->play_again = true;
    this->is_answered = false;
    this->start_game = false;

    // Creates the I/O threads
    thread input_thread(&input_loop_fn);
    thread output_thread(&output_loop_fn);

    // While the game hasn't ended
    while (this->play_again){

        // Shows the introduction screen
        this->is_answered = false;
        this->finished_game = false;
        this->intro_screen();

        // Shows the explanation screen
        if (!this->start_game)
            this->explanation_screen();

        // Starts the main game
        

        // Adds the unbreakable walls
        for (int i = 1; i < 15; i++){ 
            map->add_item(new Wall(i, 0));
            map->add_item(new Wall(i, 14));

            for (int j = 1; j < 15; j++){
                if ((j % 2 == 0) && (i % 2 == 0))
                    map->add_item(new Wall(i, j));
            }
        }

        for (int i = 0; i < 15; i++){
            map->add_item(new Wall(0, i));
            map->add_item(new Wall(14, i));
        }

        // Adds the breakable walls
        for (int i = 1; i < 15; i++){
            for (int j = 1; j < 15; j++){
                if (map->get_item(i, j) == NULL && !(rand() % 2))
                    map->add_item(new DestructibleWall(i, j));
            }
        }

        // Makes room for players to start
        map->clear_item(1, 2);
        map->clear_item(1, 1);
        map->clear_item(2, 1);
        
        map->clear_item(13, 12);
        map->clear_item(13, 13);
        map->clear_item(12, 13);

        // Adds the players to the map
        players.push_back(new Player(1, 1));
        players.push_back(new Player(13, 13));

        this->play_again = true;

        // Calls the main loop function until the game hasn't finished
        while (!this->finished_game){
            this->loop();
        }

        // Once the game has finished, shows the end of game screen 1 second after the end of the explosion
        this_thread::sleep_for(chrono::milliseconds(EXPLOSION_LIFETIME + 1000));

        // Clears the map
        for (int i = 0; i < MAP_HEIGHT; i++){
            for (int j = 0; j < MAP_WIDTH; j++){
                map->clear_item(i, j);
            }
        }

        players.clear();

        // Shows the end of game screen
        this->end_of_game_screen();
    }

    input_thread.join();
    output_thread.join();
}


// Creates the introduction screen
void Game::intro_screen(){

    vector<pair<int, int>> bomberman_letters = {make_pair(map->W / 2 - 2, 2), make_pair(map->W / 2, 2), make_pair(map->W / 2 + 2, 2), make_pair(map->W / 2 - 2, 3), make_pair(map->W / 2, 3), make_pair(map->W / 2 + 2, 3), make_pair(map->W / 2 - 1, 4), make_pair(map->W / 2 + 1, 4), make_pair(map->W / 2 - 2, 7), make_pair(map->W / 2 + 2, 7), make_pair(map->W / 2 - 2, 8), make_pair(map->W / 2 + 2, 8), make_pair(map->W / 2 - 1, 12), make_pair(map->W / 2, 13), make_pair(map->W / 2 - 1, 14), make_pair(map->W / 2 - 2, 18), make_pair(map->W / 2, 18), make_pair(map->W / 2 + 2, 18), make_pair(map->W / 2 - 2, 19), make_pair(map->W / 2, 19), make_pair(map->W / 2 + 2, 19), make_pair(map->W / 2 - 1, 20), make_pair(map->W / 2 + 1, 20), make_pair(map->W / 2 - 2, 23), make_pair(map->W / 2, 23), make_pair(map->W / 2 + 2, 23), make_pair(map->W / 2 - 2, 24), make_pair(map->W / 2, 24), make_pair(map->W / 2 + 2, 24), make_pair(map->W / 2 - 2, 25), make_pair(map->W / 2, 25), make_pair(map->W / 2 + 2, 25), make_pair(map->W / 2 - 2, 28), make_pair(map->W / 2, 28), make_pair(map->W / 2 - 2, 29), make_pair(map->W / 2, 29), make_pair(map->W / 2 - 1, 30), make_pair(map->W / 2 + 1, 29), make_pair(map->W / 2 + 2, 30), make_pair(map->W / 2 - 1, 33), make_pair(map->W / 2, 34), make_pair(map->W / 2 - 1, 35), make_pair(map->W / 2 - 2, 42), make_pair(map->W / 2 - 1, 41), make_pair(map->W / 2 - 1, 43), make_pair(map->W / 2, 40), make_pair(map->W / 2, 44), make_pair(map->W / 2 + 2, 38), make_pair(map->W / 2 + 2, 46), make_pair(map->W / 2 - 1, 49), make_pair(map->W / 2, 50), make_pair(map->W / 2 + 1, 51)};

    // B
    //cout << "MAP_HEIGHT = " << map->H << " MAP_WIDTH = " << map->W << endl;
    for (int i = map->W / 2 - 2; i < map->W / 2 + 3; i++){
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
    
    for (int i = 39; i < 46; i++){
        map->add_item(new Wall(map->W / 2 + 1, i));
    }

    for (pair<int, int> p : bomberman_letters){
        map->add_item(new Wall(p.first, p.second));
    }

    // Put star in intro_screen
    for (int i = 0; i < map->W / 2 - 2; i++){
        map->add_item(new Item(i, i + 2, false, false, '*' | A_BOLD));
        map->add_item(new Item(i, map->H / 2, false, false, '*' | A_BOLD));
        map->add_item(new Item(i, map->H - i - 2, false, false, '*' | A_BOLD));
    }

    for (int i = map->W / 2 + 3; i < map->W; i++){
        map->add_item(new Item(i, i + map->H / 2, false, false, '*' | A_BOLD));
        map->add_item(new Item(i, map->H / 2, false, false, '*' | A_BOLD));
        map->add_item(new Item(i, map->H / 2 - i, false, false, '*' | A_BOLD));
    }

    this_thread::sleep_for(chrono::milliseconds(1000));

    // Clears the map
    for (int i = 0; i < map->W; i++){
        for (int j = 0; j < map->H; j++){
            map->clear_item(i, j);
        }
    }
}


// Creates the explanation screen
void Game::explanation_screen(){

    vector<string> explanation_player = {"@", "->", "Player's", "Bomb"};
    vector<string> explanation_Dest_Wall = {"#", "->", "Destructible", "Wall"};
    vector<string> explanation_Bomb_R = {"@", "->", "Increase", "Bomb", "Range"};
    vector<string> explanation_Inc_Bombs = {"$", "->", "Increase", "max", "number", "of", "bombs"};
    vector<string> pressionarEnter = {"pressione", "ENTER", "para", "continuar"};

    vector<pair<int, int>> symbols_letters = {make_pair(3, 12), make_pair(3, 13), make_pair(3, 14), make_pair(4, 12), make_pair(5, 12), make_pair(5, 13), make_pair(5, 14), make_pair(6, 14), make_pair(7, 12), make_pair(7, 13), make_pair(7, 14), make_pair(3, 16), make_pair(4, 17), make_pair(5, 18), make_pair(4, 19), make_pair(3, 20), make_pair(6, 18), make_pair(7, 18), make_pair(4, 22), make_pair(5, 23), make_pair(4, 24), make_pair(3, 28), make_pair(3, 29), make_pair(5, 28), make_pair(5, 29), make_pair(7, 28), make_pair(7, 29), make_pair(4, 30), make_pair(6, 30), make_pair(3, 33), make_pair(3, 34), make_pair(7, 33), make_pair(7, 34), make_pair(7, 38), make_pair(7, 39), make_pair(7, 40), make_pair(3, 42), make_pair(3, 43), make_pair(3, 44), make_pair(4, 42), make_pair(5, 42), make_pair(5, 43), make_pair(5, 44), make_pair(6, 44), make_pair(7, 42), make_pair(7, 43), make_pair(7, 44)};

    // Construct the explanation screen
    for (int i = 3; i < 8; i++){
        map->add_item(new Wall(i, 21));
        map->add_item(new Wall(i, 25));
        map->add_item(new Wall(i, 27));
        map->add_item(new Wall(i, 32));
        map->add_item(new Wall(i, 35));
        map->add_item(new Wall(i, 37));
    }

    for (pair<int, int> p : symbols_letters){
        map->add_item(new Wall(p.first, p.second));
    }

    // explaining symbols:

    // + -> Player's bomb
    int col = 8;
    for (string str : explanation_player){
        for (int i = 0; i < (int)str.size(); i++, col++){
            map->add_item(new Item(10, col, false, false, str[i] | A_BOLD));
        }
        col++;
    }

    // # -> Destructible Wall
    col = 8;
    for (string str : explanation_Dest_Wall){
        for (int i = 0; i < (int)str.size(); i++, col++)
            map->add_item(new Item(12, col, false, false, str[i] | A_BOLD));
        col++;
    }

    // @ -> Increase bomb range

    col = 8;
    for (string str : explanation_Bomb_R){
        for (int i = 0; i < (int)str.size(); i++, col++)
            map->add_item(new Item(14, col, false, false, str[i] | A_BOLD));
        col++;
    }

    // $ -> Increase max bombs
    col = 8;
    for (string str : explanation_Inc_Bombs){
        for (int i = 0; i < (int)str.size(); i++, col++)
            map->add_item(new Item(16, col, false, false, str[i] | A_BOLD));
        col++;
    }

    this_thread::sleep_for(chrono::milliseconds(500));

    // pressione ENTER para continuar
    col = 9;
    for (string str : pressionarEnter){
        for (int i = 0; i < (int)str.size(); i++, col++){
            map->add_item(new Item(map->W - 2, col, false, false, str[i] | A_BOLD));
            this_thread::sleep_for(chrono::milliseconds(150));
        }
        col++;
    }

    while (!this->start_game);

    // clear map
    for (int i = 0; i < map->W; i++){
        for (int j = 0; j < map->H; j++)
            map->clear_item(i, j);
    }
}


// Main Game Loop
// Checks for collisions of the player with any items
void Game::loop(){

    // Repeats for each player
    for (int i = 0; i < players.size(); i++){

        // Gets the player's coordinates
        int x, y;
        players[i]->get_coordinates(x, y);

        // Checks if there's an item in that position
        Item *item = map->get_item(x, y);

        // Calls the items' collision function if applicable
        if (item != NULL)
            item->collide(players[i]);
    }

    this_thread::sleep_for(chrono::milliseconds(33));
}


// Constructs the end of game screen
void Game::end_of_game_screen(){

    vector<pair<int, int>> end_of_game_letters = {make_pair(1, 25), make_pair(4, 28), make_pair(5, 29), make_pair(6, 30), make_pair(5, 31), make_pair(4, 32), make_pair(10, 22), make_pair(11, 23), make_pair(12, 24), make_pair(13, 23), make_pair(14, 22), make_pair(17, 14), make_pair(17, 15), make_pair(17, 16), make_pair(17, 17), make_pair(17, 18), make_pair(22, 15), make_pair(22, 14), make_pair(21, 14), make_pair(17, 21), make_pair(22, 21), make_pair(17, 22), make_pair(22, 22), make_pair(17, 26), make_pair(17, 27), make_pair(17, 28), make_pair(22, 26), make_pair(22, 27), make_pair(22, 28), make_pair(21, 28), make_pair(20, 28), make_pair(20, 27), make_pair(20, 29), make_pair(20, 30), make_pair(21, 30), make_pair(17, 33), make_pair(22, 33), make_pair(17, 34), make_pair(22, 34)};

    // Construir a tela de ganhador

    for (int i = 3; i < 8; i++){
        map->add_item(new Wall(i, 18));
        map->add_item(new Wall(i, 25));
        map->add_item(new Wall(i, 27));
        map->add_item(new Wall(i, 33));
    }
    for (int j = 19; j < 23; j++){
        map->add_item(new Wall(3, j));
        map->add_item(new Wall(6, j));
    }

    for (int i = 10; i < 15; i++){
        map->add_item(new Wall(i, 21));
    }
    for (int i = 10; i < 15; i++){
        map->add_item(new Wall(i, 26));
    }

    for (int i = 27; i < 31; i++){
        map->add_item(new Wall(10, i));
        map->add_item(new Wall(12, i));
        map->add_item(new Wall(14, i));
    }

    for (int i = 17; i < 23; i++){
        map->add_item(new Wall(i, 16));
    }

    for (int i = 17; i < 23; i++){
        map->add_item(new Wall(i, 20));
        map->add_item(new Wall(i, 23));
    }
    
    for (int i = 17; i < 23; i++){
        map->add_item(new Wall(i, 25));
    }
    
    for (int i = 17; i < 23; i++){
        map->add_item(new Wall(i, 32));
        map->add_item(new Wall(i, 35));
    }

    for (pair<int, int> p : end_of_game_letters){
        map->add_item(new Wall(p.first, p.second));
    }

    for (int i = 0; i < MAP_HEIGHT; i++){
        map->add_item(new Star(i, 0));
        map->add_item(new Star(i, MAP_WIDTH - 1));
    }
    
    for (int i = 0; i < MAP_WIDTH - 1; i++){
        map->add_item(new Star(0, i));
        map->add_item(new Star(MAP_HEIGHT - 1, i));
    }

    // Play again

    vector<string> jogar_novamente = {"JOGAR", "NOVAMENTE?", "(ENTER)", "Sim", "(Q)", "Nao"};

    int col = 8;
    for (string str : jogar_novamente){
        for (int i = 0; i < (int)str.size(); i++, col++)
            map->add_item(new Item(map->W - 2, col, false, false, str[i] | A_BOLD));
        col++;
    }

    // Delay
    while (!this->is_answered);

    // Clears the screen
    for (int i = 0; i < map->W; i++){
        for (int j = 0; j < map->H; j++)
            map->clear_item(i, j);
    }
}
