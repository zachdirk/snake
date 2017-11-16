#include "Snake.h"
#include "Grid.h"
#include <stdlib.h>
#include <iostream>
void SnakeBody::setCol(int col){
    mPrevCol = mCol;
    mCol = col;
}

void SnakeBody::setRow(int row){
    mPrevRow = mRow;
    mRow = row;
}

void SnakeBody::init(int col, int row){
    mPrev = NULL;
    mCol = col;
    mRow = row;
    mPrevCol = -1;
    mPrevRow = -1;
}

void Snake::move(int col, int row){
    SnakeBody* body = &mHead;
    int newRow = row;
    int newCol = col;
    int currRow;
    int currCol;
    while(body != NULL){
        currRow = body->getRow();
        currCol = body->getCol();
        body->setCol(newCol);
        body->setRow(newRow);
        newRow = currRow;
        newCol = currCol;
        body = body->getPrev();
    }
}

void Snake::init(int col, int row){
    mD = Snake::RIGHT;
    mHead.init(col, row);
}

void SnakeBody::setPrev(SnakeBody* body){
    mPrev = body;
}

void Snake::grow(){
    std::cout << "Growing" << std::endl;
    SnakeBody* body = &mHead;
    int i = 1;
    while(body->getPrev() != NULL){
        body = body->getPrev();
    }
    int row = body->getPrevRow();
    int col = body->getPrevCol();
    SnakeBody* newBody = new SnakeBody;
    newBody->init(col, row);
    body->setPrev(newBody);
    mTail = *newBody;
}

void Snake::draw(Grid* grid){
    SnakeBody* body = &mHead;
    int col = body->getCol();
    int row = body->getRow();
    grid->set(col, row, Grid::SNAKEHEAD);
    while(body->getPrev() != NULL){
        body = body->getPrev();
        col = body->getCol();
        row = body->getRow();
        grid->set(col, row, Grid::SNAKEBODY);
    }
    col = body->getPrevCol();
    row = body->getPrevRow();
    if (col > -1 && row > -1)
        grid->set(col, row, Grid::EMPTY);
}

void Snake::destroy(){
    SnakeBody* body = mHead.getPrev();
    SnakeBody* next;
    while (body != NULL){
        next = body->getPrev();
        free(body);
        body = next;
    }
    mHead.setPrev(NULL);
}