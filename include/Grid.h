#ifndef GRID_H
#define GRID_H
#include <SDL.h>

class Grid {

    public:
        enum GridType{
            EMPTY,
            SNAKEHEAD,
            SNAKEBODY,
            FRUIT
        };

        Grid();
        ~Grid();
        void init(int h, int w, int cellSize, int gridLineSize);
        int getCols(){return mCols;}
        int getRows(){return mRows;}
        int at(int col, int row);
        void clear();
        void set(int col, int row, int val);
        void draw(SDL_Renderer* renderer);
        
    private:
        int** mArray;
        int mRows;
        int mCols;
        int mCellSize;
        int mGridLineSize;
};

#endif