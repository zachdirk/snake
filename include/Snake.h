#ifndef SNAKE_H
#define SNAKE_H
#include "Grid.h"
class SnakeBody{
    public:
        SnakeBody* getPrev(){return mPrev;}
        void setCol(int col);
        void setRow(int row);
        void setPrev(SnakeBody* body);
        int getCol(){return mCol;}
        int getRow(){return mRow;}
        int getPrevCol(){return mPrevCol;}
        int getPrevRow(){return mPrevRow;}
        void init(int col, int row);
    private:
        SnakeBody* mPrev;
        int mCol;
        int mPrevCol;
        int mRow;
        int mPrevRow;
};

class Snake{
    public:
        enum DIRECTION {
            UP,
            UPRIGHT,
            RIGHT,
            DOWNRIGHT,
            DOWN,
            DOWNLEFT,
            LEFT,
            UPLEFT
        };
        DIRECTION getDirection(){return mD;}
        SnakeBody getHead(){return mHead;}
        SnakeBody getTail(){return mTail;}
        void setDirection(DIRECTION d){mD = d;}
        void init(int col, int row);
        void move(int col, int row);
        void grow();
        void draw(Grid* grid);
        void destroy();
    private:
        DIRECTION mD;
        SnakeBody mHead;
        SnakeBody mTail;
};

#endif