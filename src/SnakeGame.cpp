#include <SDL.h>
#include <iostream>
#include "Grid.h"
#include "Snake.h"
#include "SnakeGame.h"

SnakeGame::SnakeGame(int rows, int cols, int cellSize){
    mSCREEN_HEIGHT = rows * cellSize;
    mSCREEN_WIDTH = cols * cellSize;
    mGrid.init(mSCREEN_HEIGHT, mSCREEN_WIDTH, cellSize, 1);
    mStartingCol = mGrid.getCols()/2;
    mStartingRow = mGrid.getRows()/2;
}

bool SnakeGame::pause(bool quit){
    SDL_Event e;
    bool paused = true;
    while (paused && !quit){
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT){
                quit = true;
            } 
            else if (e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_SPACE:
                        paused = false;
                        break;
                }
            }
        }
    }
    return(quit);
}

void SnakeGame::spawnSnake(){
    mSnake.init(mStartingCol, mStartingRow, &mGrid);
}

void SnakeGame::spawnFruit(){
    bool spawned = false;
    int col;
    int row;
    while (!spawned) {
        col = rand() % mGrid.getCols();
        row = rand() % mGrid.getRows();
        if (mGrid.at(col, row) == Grid::EMPTY){
            mGrid.set(col, row, Grid::FRUIT);
            spawned = true;
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
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        //we check what keys are held down, then assign a new direction based on that. 
        //we also check to make sure that the snake isn't trying to go the polar opposite direction
        //because that's where its tail would be and that just feels crappy to die that way
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
        int type = moveSnake();
        switch(type){
            case Grid::FRUIT:
                mSnake.grow();
                //need to draw before we spawn the fruit or else it could spawn the fruit where we are going to add the tail
                mSnake.draw(&mGrid); 
                spawnFruit();
                break;
            case Grid::EMPTY:
                mSnake.draw(&mGrid);
            break;
            case Grid::SNAKEHEAD:
            case Grid::SNAKEBODY:
                mSnake.draw(&mGrid);
                quit = lose(quit);
            //lose 
            break;
            default:
            //this should not happen
            break;
        }
        mGrid.draw(mRenderer);
        SDL_RenderPresent(mRenderer);
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT){
                quit = true;
            } 
            else if (e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_SPACE:
                        quit = pause(quit);
                        break;
                    case SDLK_ESCAPE:
                        restart();
                        break;
                }
            }
        }
        SDL_Delay(75);
    }
    return(true);

}

int SnakeGame::moveSnake(){
    int col = mSnake.getHead().getCol();
    int row = mSnake.getHead().getRow();
    mGrid.set(col, row, Grid::EMPTY);
    int rows = mGrid.getRows() - 1; //-1 because the array indexes from 0 to mRows-1
    int cols = mGrid.getCols() - 1; //-1 because the array indexes from 0 to mCols-1
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
    return t;
}

void SnakeGame::restart(){
    //clean
    mGrid.clear();
    mSnake.reset(mStartingCol, mStartingRow, Snake::RIGHT);
    mGrid.set(mStartingCol, mStartingRow, Grid::SNAKEHEAD);
    spawnFruit();
}

bool SnakeGame::lose(bool quit){
    SDL_Event e;
    bool paused = true;
    while (paused && !quit){
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT){
                quit = true;
            } 
            else if (e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_ESCAPE:
                        paused = false;
                        break;
                }
            }
        }
    }
    restart();
    return(quit);
}