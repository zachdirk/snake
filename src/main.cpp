#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "SnakeGame.h"

int main(int argc, char* args[]){
    int rows;
    int cols;
    int cellSize;
    if (argc == 1){
        rows = 24;
        cols = 24;
        cellSize = 20;
    } else if (argc == 4){
        rows = atol(args[1]);
        cols = atol(args[2]);
        cellSize = atol(args[3]);
    }
    SnakeGame game(cols, rows, cellSize);
    game.init();
    game.run();
    return 0;
}