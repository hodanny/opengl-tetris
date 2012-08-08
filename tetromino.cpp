/********************
Created By: Dan Ho (301050375)
Date: June 14 2012

CMPT 361: Computer Graphics
Assignment 1: Tetris
*********************/
#include "tetromino.hpp"
#include <cstdlib>
#include <GL/gl.h>

//default mapping for tetromino blocks
const char *blocks[] = 
    {
    
      "oooo" // O
      "o**o"
      "o**o"
      "oooo", 
      
      "oo*o" // I
      "oo*o"
      "oo*o"
      "oo*o", 

      "oooo" // S
      "oo**"
      "o**o"
      "oooo", 
      
      "oooo" // Z
      "o**o"
      "oo**"
      "oooo", 

      "oooo" // L
      "o***"
      "o*oo"
      "oooo", 
      
      "oooo" // J
      "o***"
      "ooo*"
      "oooo", 

      "oooo" // T
      "o***"
      "oo*o"
      "oooo" 
    };


  const struct 
  {
    int x, y;
  } rotationMat[][16] = {
    {{ 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, 
      { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, 
      { 2, 0 }, { 2, 1 }, { 2, 2 }, { 2, 3 }, 
      { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 }},
    {{ 3, 0 }, { 2, 0 }, { 1, 0 }, { 0, 0 }, 
      { 3, 1 }, { 2, 1 }, { 1, 1 }, { 0, 1 }, 
      { 3, 2 }, { 2, 2 }, { 1, 2 }, { 0, 2 }, 
      { 3, 3 }, { 2, 3 }, { 1, 3 }, { 0, 3 }},
    {{ 3, 3 }, { 3, 2 }, { 3, 1 }, { 3, 0 }, 
      { 2, 3 }, { 2, 2 }, { 2, 1 }, { 2, 0 }, 
      { 1, 3 }, { 1, 2 }, { 1, 1 }, { 1, 0 }, 
      { 0, 3 }, { 0, 2 }, { 0, 1 }, { 0, 0 }},
    {{ 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 }, 
      { 0, 2 }, { 1, 2 }, { 2, 2 }, { 3, 2 }, 
      { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, 
      { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }}
  };

int Tetromino::getX()
{
	return _x;
}

int Tetromino::getY()
{
	return _y;
}

Tetromino::Tetromino(Block block)
{ 
	_block = block; 
	_pivot = rand() % 4; 
	_x = 3;
	_y = 0;
}
				 
void Tetromino::draw()
{
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			//only draw in block if the matrix values are true
			if (map(x, y))
			{
				
		    //set vertex coordinates
			int x1 = (x+_x)*8;
			int y1 = (y+_y)*8;
			int x2 = (x+_x+1)*8;
			int y2 = (y+_y+1)*8;
			
			//color the blocks
			switch(_block)
			{
				case I:
					glColor3f(0,1,1);
					break;
				case J:
					glColor3f(0,1,0);
					break;
				case L:
					glColor3f(0,0,1);
					break;
				case O:
					glColor3f(1,1,0);
					break;
				case S:
					glColor3f(1,0,1);
					break;
				case Z:
					glColor3f(1,0,0);
					break;
				case T:
					glColor3f(1,0.5,1);
					break;
			}
	
			//draw squares to
			glBegin(GL_QUADS);
			glVertex2f(x1, y1);
			glVertex2f(x2,y1);
			glVertex2f(x2, y2);
			glVertex2f(x1, y2);
			glEnd();
			
			//outline blocks
			glColor3f(0,0,0);
			glBegin(GL_LINES);
			glVertex2f(x1, y1);
			glVertex2f(x2,y1);
			glVertex2f(x1, y1);
			glVertex2f(x1,y2);
			glVertex2f(x2, y1);
			glVertex2f(x2,y2);
			glVertex2f(x1, y2);
			glVertex2f(x2,y2);
			glEnd();
			}
		}
	}
}

bool Tetromino::map(int x, int y)
{
	bool isBlock = false;
	
	//rotates each point in the 4x4 matrix to the correct location depending on the rotation angle
	int translationIndex = rotationMat[_pivot][y*4+x].y *4 + rotationMat[_pivot][y*4+x].x;
	
	if(blocks[_block][translationIndex] == '*')
	{
		isBlock = true;
	}
	return isBlock;
}

//moves the block on the orthogonal plane
void Tetromino::move(int x, int y)
{
	_x += x;
	_y += y;
}

//updates pivot to correspond to the correct rotation matrix
void Tetromino::rotateCCW()
{
	_pivot = (_pivot + 3) % 4;
}
