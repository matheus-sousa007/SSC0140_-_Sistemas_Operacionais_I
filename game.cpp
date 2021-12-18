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

Game::Game(){
    this -> map = new Map(15,15);
} 

void Game::start(){
    players.push_back(new Player(2,1));
    players.push_back(new Player(6,5));

    for (int i = 1; i < this -> map -> W - 1; i++){
        map -> add_item(new Wall(i,0));
        map -> add_item(new Wall(i,map -> H - 1));
    
        for (int j = 1; j < this -> map -> H - 1; j++){
            if ((j % 2 == 0) && (i % 2 == 0))
                map -> add_item(new Wall(i,j));

            if ((j % 4 == 1) && (i % 4 == 1))
                map -> add_item(new DestructibleWall(i,j));
        }
    }

    for (int i = 0; i < this -> map -> H; i++){
        map -> add_item(new Wall(0,i));
        map -> add_item(new Wall(map -> W - 1,i));
    }

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