#ifndef SNAKE_H
#define SNAKE_H

class SnakeBody{
    public:
        SnakeBody* getPrev(){return mPrev;}
        void setCol(int col){mCol = col;}
        void setRow(int row){mRow = row;}
        int getCol(){return mCol;}
        int getRow(){return mRow;}
        void init(int col, int row);
    private:
        SnakeBody* mPrev;
        int mCol;
        int mRow;
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
    private:
        DIRECTION mD;
        SnakeBody mHead;
        SnakeBody mTail;
};

#endif