#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "Grid.h"

class SnakeGame{
    public:
        SnakeGame();
        bool init();
        bool run();
        void quit();
    private:
        const int mSCREEN_WIDTH = 640; // 642/20 = 32 grid cells + 2 for the borders at the start and end
        const int mSCREEN_HEIGHT = 480; // 480/20 = 24 grid cells + 2 for the borders at the start and end
        Grid mGrid;
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;
};

#endif