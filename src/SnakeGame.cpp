#include <SDL.h>
#include <iostream>
#include "SnakeGame.h"
#include "Grid.h"
#include "Snake.h"

SnakeGame::SnakeGame(){
    mGrid.init(mSCREEN_HEIGHT, mSCREEN_WIDTH, 20, 1);
}

void SnakeGame::spawnSnake(){
    int row = mGrid.getRows()/2;
    int col = mGrid.getCols()/2;
    mGrid.set(col, row, Grid::SNAKEHEAD);
    mSnake.init(col, row);
}

void SnakeGame::spawnFruit(){
    bool set = true;
    int col;
    int row;
    while (set) {
        col = rand() % mGrid.getCols();
        row = rand() % mGrid.getRows();
        if (mGrid.at(col, row) == Grid::EMPTY){
            mGrid.set(col, row, Grid::FRUIT);
            set = false;
        }
    }
}

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
    SDL_RenderClear(mRenderer);
    return(true);
}

bool SnakeGame::run(){
    bool quit = false;
    SDL_Event e;
    spawnSnake();
    spawnFruit();
    while (!quit){
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT){
                quit = true;
            } 
            /*else if (e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        mSnake.setDirection(Snake::UP);
                        break;
                    case SDLK_DOWN:
                        mSnake.setDirection(Snake::DOWN);
                        break;
                    case SDLK_RIGHT:
                        mSnake.setDirection(Snake::RIGHT);
                        break;
                    case SDLK_LEFT:
                        mSnake.setDirection(Snake::LEFT);
                        break;
                    default:
                        //do nothing
                        break;
                }
            }*/
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT]){
            if (mSnake.getDirection() != Snake::DOWNLEFT)
                mSnake.setDirection(Snake::UPRIGHT);
        } else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_LEFT]){
            if (mSnake.getDirection() != Snake::DOWNRIGHT)
                mSnake.setDirection(Snake::UPLEFT);
        } else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_RIGHT]){ 
            if (mSnake.getDirection() != Snake::UPLEFT)
                mSnake.setDirection(Snake::DOWNRIGHT);
        } else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_LEFT]){
            if (mSnake.getDirection() != Snake::UPRIGHT)
                mSnake.setDirection(Snake::DOWNLEFT);
        } else if (currentKeyStates[SDL_SCANCODE_RIGHT]){
            if (mSnake.getDirection() != Snake::LEFT)
                mSnake.setDirection(Snake::RIGHT);
        } else if (currentKeyStates[SDL_SCANCODE_DOWN]){
            if (mSnake.getDirection() != Snake::UP)
                mSnake.setDirection(Snake::DOWN);
        } else if (currentKeyStates[SDL_SCANCODE_LEFT]){ 
            if (mSnake.getDirection() != Snake::RIGHT)
                mSnake.setDirection(Snake::LEFT);
        } else if (currentKeyStates[SDL_SCANCODE_UP]){
            if (mSnake.getDirection() != Snake::DOWN)
                mSnake.setDirection(Snake::UP);
        }

        std::cout << mSnake.getHead().getCol() << ", " << mSnake.getHead().getRow() << std::endl;
        int type = moveSnake();
        switch(type){
            case Grid::FRUIT:
            //make snake longer
            spawnFruit();
            break;
            default:
            //this should not happen
            break;
        }
        std::cout << mSnake.getHead().getCol() << ", " << mSnake.getHead().getRow() << std::endl;
        mGrid.draw(mRenderer);
        SDL_RenderPresent(mRenderer);
        SDL_Delay(75);
    }
    return(true);

}

int SnakeGame::moveSnake(){
    int col = mSnake.getHead().getCol();
    int row = mSnake.getHead().getRow();
    mGrid.set(col, row, Grid::EMPTY);
    int rows = mGrid.getRows() - 1; //-1 because the array indexes from 0 to x-1 and not 1 to x
    int cols = mGrid.getCols() - 1; //-1 because the array indexes from 0 to x-1 and not 1 to x
    switch(mSnake.getDirection()){
        case Snake::UP:
            row = row - 1;
        break;
        case Snake::UPRIGHT:
            row = row - 1;
            col = col + 1;
        break;
        case Snake::UPLEFT:
            row = row - 1;
            col = col - 1;
        break;
        case Snake::DOWN:
            row = row + 1;
        break;
        case Snake::DOWNRIGHT:
            row = row + 1;
            col = col + 1;
        break;
        case Snake::DOWNLEFT:
            row = row + 1;
            col = col - 1;
        break;
        case Snake::LEFT:
            col = col - 1;
        break;
        case Snake::RIGHT:
            col = col + 1;
        break;
        default:
        //should never happen
        break;
    }
    
    if (col < 0)
        col = cols;
    if (col > cols)
        col = 0;
    if (row < 0)
        row = rows;
    if (row > rows)
        row = 0;
    mSnake.move(col, row);
    int t = mGrid.at(col, row);
    mGrid.set(col, row, Grid::SNAKEHEAD);
    return t;
}