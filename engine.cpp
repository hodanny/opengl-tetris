/********************
Created By: Dan Ho (301050375)
Date: June 14 2012

CMPT 361: Computer Graphics
Assignment 1: Tetris
*********************/
#include "engine.hpp"
#include <cstdlib>
#include <ctime>

Engine::Engine(): _tetromino(Tetromino::Block(rand() % 7)) 
{ 
	srand(time(0)); //initialize random seed inorder to randomize tetris blocks
}


void Engine::draw()
{
	_grid.draw();
	_tetromino.draw();
}

//redraw grid and block
void Engine::restart()
{
	_grid = Grid();
	_tetromino = Tetromino(Tetromino::Block(rand()%7));
}

//each clock iteration will move the block along the y-axis
void Engine::clock()
{
	Tetromino activeBlock = _tetromino;
	activeBlock.move(0,1);

	//block has not hit wall or another block
	if(!_grid.collides(activeBlock))
	{
		_tetromino = activeBlock;
	}
	//update the grid and create a new tetromino
	else
	{
		_grid.join(_tetromino);
		_grid.removeLines();
		//create new block
		_tetromino = Tetromino(Tetromino::Block(rand() % 7)); 
		if(_grid.collides(_tetromino)) //check for collision at the top
		{
			restart();
		}
	}
}

//key mapping
void Engine::keyHandler(Direction direction)
{
  Tetromino block = _tetromino;
  switch(direction)
  {
  case UP:
    block.rotateCCW();
  break;
  case DOWN:
    block.move(0,1);
    break;
  break;
  case LEFT:
    block.move(-1,0);
    break;
  case RIGHT:
    block.move(1,0);
    break;
  case SPACE:
    while(!_grid.collides(block))
    {
   		 block.move(0,1);
	    _tetromino = block;
    }
    break;
  }
  
  if(!_grid.collides(block)) //block doesn't collide, redraw the block
    _tetromino = block;
}
