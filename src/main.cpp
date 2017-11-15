#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "SnakeGame.h"

int main(int argc, char* args[]){
    SnakeGame game;
    game.init();
    game.run();
    return 0;
}