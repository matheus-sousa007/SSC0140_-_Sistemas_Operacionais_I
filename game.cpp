#include <thread>
#include <math.h>
#include <ncurses.h>    
using namespace std;

#include "game.h"
#include "input.h"
#include "output.h"
#include "player.h"
#include "bomb.h"
#include "map.h"

#define MAP_HEIGHT 25
#define MAP_WIDTH 55

Game::Game(){
    this -> map = new Map(MAP_HEIGHT, MAP_WIDTH);
} 

void Game::start(){

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
            if (map->get_item(i, j) == NULL && rand() % 3)
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
    players.push_back(new Player(map->W - 2, map->H - 2));

    thread input_thread(&input_loop_fn);
    thread output_thread(&output_loop_fn);
    
    while (true){
        this -> loop();
    }
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