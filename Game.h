// Program 1:	tjr0023_3
// Name: 		Tyler Robins
// Class: 		COMP 2710 Section 1
// Date:		11/18/2017
// Email:		tjr0023@auburn.edu
//
// Description: This is the header file for the Game program. 
//              It contains all of the variables and functions of the Game program.
//


#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Node.h"
#include <cstdlib>
#include <cstring>
#include <map>
using namespace std;

class Game
{
public:
	void createBoard(string);
	void enterUsers();
	void turn(int);
	void move(int, int);
	void snakeOrLadder(int);
	void endGame(int);
	void runGame();
	void switchNode(int, int);
	string paths(int);
private:
	int startNode;
	int endNode;
	int nPlayers;
	int maxNodes;
	int directions;
	Node* board;
	Node* playerNode;
	string* players;
	string* playerMoves;
	int* playerSteps;
	
};

	
	