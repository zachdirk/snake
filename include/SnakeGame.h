#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "Grid.h"
#include "Snake.h"

class SnakeGame{
    public:
        SnakeGame(int rows, int cols, int cellSize);
        bool init();
        bool run();
        void quit();
        bool pause(bool quit);
        void spawnFruit();
        void spawnSnake();
        void restart();
        bool lose(bool quit);
        int moveSnake();
    private:
        int mSCREEN_WIDTH;
        int mSCREEN_HEIGHT;
        int mStartingCol;
        int mStartingRow;
        Snake mSnake;
        Grid mGrid;
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;
};

#endif