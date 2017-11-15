#ifndef GRID_H
#define GRID_H
#include <SDL.h>

class Grid {

    public:
        Grid();
        ~Grid();

        void init(int x, int y, int cellSize, int gridLineSize);
        int at(int x, int y);
        int set(int x, int y, int val);
        void draw(SDL_Renderer* renderer);
        enum GridType{
            EMPTY,
            SNAKEHEAD,
            SNAKETAIL,
            FRUIT
        };
    private:
        int** mArray;
        int mRows;
        int mCols;
        int mCellSize;
        int mGridLineSize;
};

#endif