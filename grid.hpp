/********************
Created By: Dan Ho (301050375)
Date: June 14 2012

CMPT 361: Computer Graphics
Assignment 1: Tetris
*********************/

class Tetromino;
class Grid
{
public:
	enum { WIDTH = 10, HEIGHT = 20 };
    Grid();
    void draw();
    bool collides(Tetromino block);
    void join(Tetromino block);
    void removeLines();
    
private:
    bool _grid[HEIGHT][WIDTH];
};
