#ifndef SNAKEGAME_H
#define SNAKEGAME_H

class SnakeGame{
    public:
        SnakeGame();
        bool init();
        bool run();
    private:
        const int mSCREEN_HEIGHT = 480;
        const int mSCREEN_WIDTH = 640;
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;
};

#endif