/********************
Created By: Dan Ho (301050375)
Date: June 14 2012

CMPT 361: Computer Graphics
Assignment 1: Tetris
*********************/
#include "engine.hpp"
#include <GL/glut.h>

Engine game;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);     
	game.draw();
	glutSwapBuffers();
}

void timer(int init)
{
	game.clock();
	display();
	glutTimerFunc(750, timer, 0);
}

void specialKeys( int key, int x, int y )
{
	switch ( key ) {
	case GLUT_KEY_RIGHT:
		game.keyHandler(Engine::RIGHT);
		break;
	case GLUT_KEY_LEFT:
		game.keyHandler(Engine::LEFT);
		break;
	case GLUT_KEY_UP:
		game.keyHandler(Engine::UP);
		break;
	case GLUT_KEY_DOWN:
		game.keyHandler(Engine::DOWN);
		break;
	}
	display();
}

void keyboard (unsigned char key, int x, int y)
{
	switch(key){
	case 113: //q
		exit(EXIT_SUCCESS);
		break;
	case 114: //r
		game.restart();
		break;
	case 32: //space
		//game.keyHandler(Engine::SPACE);
		break;
	}
	display();
}

int main( int argc, char **argv )
{
	int const xSize = 250;
	int const ySize = 500;
	// Initialize glut library
	glutInit(&argc, argv);

	// Create the window
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(xSize, ySize);
	glutInitWindowPosition(1000, 500);
	glutCreateWindow("CMPT361: Tetris");
	glClearColor(0,0,.25,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 8*Grid::WIDTH, 8*Grid::HEIGHT, 0, 0, 1.0);
	glDisable(GL_DEPTH_TEST);
	glutDisplayFunc( display );
	timer(0);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
