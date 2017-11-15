#ifndef GRID_H
#define GRID_H
#include <SDL.h>

class Grid {

    public:
        Grid();
        ~Grid();

        void init(int h, int w, int cellSize, int gridLineSize);
        int getCols(){return mCols;}
        int getRows(){return mRows;}
        int at(int col, int row);
        void set(int col, int row, int val);
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