#ifndef SNAKE_H
#define SNAKE_H

class SnakeTail{
    public:
        SnakeTail* getNext(){return mNext;}
        SnakeTail* getPrev(){return mPrev;}
        int getCol(){return mCol;}
        int getRow(){return mRow;}
    private:
        SnakeTail* mNext;
        SnakeTail* mPrev;
        int mCol;
        int mRow;
};

class SnakeHead{
    public:
        SnakeTail* getPrev(){return mPrev;}
        void setCol(int col){mCol = col;}
        void setRow(int row){mRow = row;}
        int getCol(){return mCol;}
        int getRow(){return mRow;}
        void init(int col, int row);
    private:
        SnakeTail* mPrev;
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
        SnakeHead getHead(){return mHead;}
        SnakeHead getTail(){return mTail;}
        void setDirection(DIRECTION d){mD = d;}
        void init(int col, int row);
        void move(int col, int row);
    private:
        DIRECTION mD;
        SnakeHead mHead;
        SnakeHead mTail;
};

#endif