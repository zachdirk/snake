#include "Snake.h"
#include <stdlib.h>

void SnakeHead::init(int col, int row){
    mPrev = NULL;
    mCol = col;
    mRow = row;
}

void Snake::move(int col, int row){
    mHead.setCol(col);
    mHead.setRow(row);
}

void Snake::init(int col, int row){
    mD = RIGHT;
    mHead.init(col, row);
}