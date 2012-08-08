/********************
Created By: Dan Ho (301050375)
Date: June 14 2012

CMPT 361: Computer Graphics
Assignment 1: Tetris
*********************/
#include "grid.hpp"
#include "tetromino.hpp"
#include <GL/gl.h>

//initialize empty grid
Grid::Grid()
{
  for (int y = 0; y < HEIGHT; ++y)
    for (int x = 0; x < WIDTH; ++x)
      _grid[y][x] = false;
}

//redraws grid lines and current blocks that have already been placed
void Grid::draw()
{
	//draws grid lines of size 8*8
	for(int x = 0; x < WIDTH*8; x+=8)
	{
		glColor3f(0.5,0.5,0.5);
		glBegin(GL_LINES);
		glVertex2f(x, 0);
		glVertex2f(x,HEIGHT*8);
		glEnd();
	}
  
	for(int y = 0; y < HEIGHT*8; y+=8)
	{
		glColor3f(0.5,0.5,0.5);
		glBegin(GL_LINES);
		glVertex2f(0, y);
		glVertex2f(WIDTH*8,y);
		glEnd();
	}
  
  //draws the block by looking at the boolean values of the matrix
	for (int y = 0; y < HEIGHT; ++y)
		for (int x = 0; x < WIDTH; ++x)
			if (_grid[y][x])
			{
				int x1 = x*8;
				int y1 = y*8;
				int x2 = (x+1)*8;
				int y2 = (y+1)*8;
				glColor3f(1,0,0);
				glBegin(GL_QUADS);
				glVertex2f(x1, y1);
				glVertex2f(x2,y1);
				glVertex2f(x2, y2);
				glVertex2f(x1, y2);
				glEnd();
				
				//outlines the block
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

bool Grid::collides(Tetromino block)
{
	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			if(block.map(x,y))
			{
				int x_t = x + block.getX();
				int y_t = y + block.getY();
				
				//hits a wall or the floor
				if(x_t < 0 || x_t >= WIDTH || y_t < 0 || y_t >= HEIGHT)
					return true;
				//hits a block
				if(_grid[y_t][x_t])
					return true;
			}
		}
	}
	//did not collide
	return false;
}

//
void Grid::join(Tetromino block)
{
	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			//get point of the block with respect to the plane
			int x_t = x + block.getX();
			int y_t = y + block.getY();
			_grid[y_t][x_t] = _grid[y_t][x_t] || block.map(x, y); //the new block onto the grid
		}
	}
}

void Grid::removeLines()
{
	//search for completed lines from top-down for every row
	for (int y = 0; y < HEIGHT; y++)
	{
		bool rowIsSolid = true;
		for (int x = 0; x < WIDTH; x++)
		{
			//not a solid line found, go to next row
			if (!_grid[y][x])
			{
				rowIsSolid = false;
				break;
			}
		}

		if (rowIsSolid)
		{
			//set the entire row back to false
			for(int x = 0; x < WIDTH; x++)
			{
				_grid[y][x] = false;
			}
			
			//shift the boolean elements that are above the removed row, down one level
			int yCurrent = y;
			
			for(int yAbove = y-1; yAbove >= 0; yAbove--)
			{
				for(int x = 0; x < WIDTH; x++)
				{
					_grid[yCurrent][x] = _grid[yAbove][x];
				}
				yCurrent = yAbove;
			}
		}
	}
}
