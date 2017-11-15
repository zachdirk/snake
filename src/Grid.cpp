#include <SDL.h>
#include "Grid.h"
#include <iostream>
Grid::Grid(){
    mRows = 0;
    mCols = 0;
    mArray = nullptr;
}

Grid::~Grid(){
    for (int i = 0; i < mRows; i++){
        delete [] mArray[i];
    }
    delete [] mArray;
}

void Grid::init(int x, int y, int cellSize, int gridLineSize){
    mRows = x/cellSize;
    mCols = y/cellSize;
    mCellSize = cellSize;
    mGridLineSize = gridLineSize;
    mArray = new int*[mRows];
    for (int i = 0; i < mRows; i++){
       mArray[i] = new int[mCols];
       for (int j = 0; j < mCols; j++){
           mArray[i][j] = j % 4;
       }
    }
}


void Grid::draw(SDL_Renderer* renderer){
    int w = mCellSize;
    int h = mCellSize;
    for (int i = 0; i < mRows; i++){
        int y = i*mCellSize;
        for (int j = 0; j < mCols; j++){
            int x = j*mCellSize;
            SDL_Rect cellSquare = {x, y, w, h};
            switch(mArray[i][j]){
                case EMPTY:
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                break;
                case SNAKEHEAD:
                    SDL_SetRenderDrawColor(renderer, 0x59, 0x98, 0x2F, 0xFF);
                break;
                case SNAKETAIL:
                    SDL_SetRenderDrawColor(renderer, 0x33, 0x5E, 0x17, 0xFF);
                break;
                case FRUIT:
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                break;
                default:
                // this should never happen
                break;
            }
            SDL_RenderFillRect(renderer, &cellSquare);
        }
    }
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLine(renderer, 0, 0, mCols*mCellSize, 0); //draw the first column
    SDL_RenderDrawLine(renderer, 0, 0, 0, mRows*mCellSize); //draw the first row
    for (int i = 0; i <= mRows; i++){
        SDL_RenderDrawLine(renderer, 0, (i*mCellSize - 1), mCols*mCellSize, (i*mCellSize-1));
    }
    for (int i = 0; i <= mCols; i++){
        SDL_RenderDrawLine(renderer, (i*mCellSize-1), 0, (i*mCellSize-1), mRows*mCellSize);
    }
    
}

int Grid::at(int x, int y){
    return(mArray[x][y]);
}

int Grid::set(int x, int y, int val){
    mArray[x][y] = val;
    return(mArray[x][y]);
}