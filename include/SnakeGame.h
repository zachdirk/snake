#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "Grid.h"
#include "Snake.h"

class SnakeGame{
    public:
        SnakeGame();
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
        const int mSCREEN_WIDTH = 640; // 640/20 = 32 grid cells
        const int mSCREEN_HEIGHT = 480; // 480/20 = 24 grid cells
        int mStartingCol;
        int mStartingRow;
        Snake mSnake;
        Grid mGrid;
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;
};

#endif