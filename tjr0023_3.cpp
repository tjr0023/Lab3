// Program 0:	tjr0023_3
// Name: 		Tyler Robins
// Class: 		COMP 2710 Section 1
// Date:		11/18/2017
// Email:		tjr0023@auburn.edu
//
// Description: This is the main file for a Maze Game program. The file name of the
//              desired maze file can be input here. Change input of the createBoard function.
//
// How to:      To compile the program, type the following line in the terminal:
//				make
//				To execute the program, type the following line in the terminal:
//				./lab3

#include "Game.h"
#include <iostream>


int main()
{
	Game game;
	game.createBoard("Maze 1.txt");
	game.runGame();
	return 0;
}
