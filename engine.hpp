/********************
Created By: Dan Ho (301050375)
Date: June 14 2012

CMPT 361: Computer Graphics
Assignment 1: Tetris
*********************/
#include "tetromino.hpp"
#include "grid.hpp"

class Engine
{
public:
    enum Direction {UP, DOWN, LEFT, RIGHT, SPACE}; //define game keys
    Engine();
    void draw(); //draws grid and tetromino
    void clock(); //moves tetromino down every interval
    void restart();
    void keyHandler(Direction);

private:
    Grid _grid;
    Tetromino _tetromino;
};
