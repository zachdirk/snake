#include <SDL.h>
#include <iostream>
#include "SnakeGame.h"
SnakeGame::SnakeGame(){}

bool SnakeGame::init(){
    //try and initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO)){
        std::cout << "SDL failed to initialize! SDL Error: " << SDL_GetError() << std::endl;
        return(false); //on fail, return to main
    }
    //try and create a window
    mWindow = SDL_CreateWindow("Snake!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mSCREEN_WIDTH, mSCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (mWindow == NULL){
        std::cout << "Window failed to be created! SDL Error: " << SDL_GetError() << std::endl;
        return(false);
    }
    //try and create a renderer
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == NULL){
        std::cout << "Renderer failed to be created! SDL Error: " << SDL_GetError() << std::endl;
        return(false);
    }
    //set the inital render color to white
    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    return(true);
}



bool SnakeGame::run(){
    bool quit = false;
    SDL_Event e;
    while (!quit){
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT){
                quit = true;
            }
        }
    }
    return(true);
}