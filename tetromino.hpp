/********************
Created By: Dan Ho (301050375)
Date: June 14 2012

CMPT 361: Computer Graphics
Assignment 1: Tetris
*********************/
class Tetromino
{
public:

  enum Block {O, I, S, Z, L, J, T};
  
  Tetromino(Block block);
  void draw();
  void move(int dx, int dy);
  void rotateCCW(void);
  bool map(int x, int y);
  int getX();
  int getY();
  
private:
  Block _block;
  int _pivot;
  int _x;
  int _y;
};
