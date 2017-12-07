// Program 2:	tjr0023_3
// Name: 		Tyler Robins
// Class: 		COMP 2710 Section 1
// Date:		11/18/2017
// Email:		tjr0023@auburn.edu
//
// Description: This is the Game program. It creates a Maze Game with the given number of players.
//              It runs a constant loop through the players to give them turns in order. The 
//              amount of moves per turn is decided by a random number generator. 
//

#include "Game.h"

// The createBoard method creates an array of linked Nodes from the given file. 
// It will exit the program if maxNodes does not get set above zero. That means
// either the file was not found or the first line of the file is not a number.
void Game::createBoard(string filenameIn)
{
	string startString, endString, temp, nodeName;
	Node *tempNode;
	string star = "*";
	int index;
	directions = 5;
	
	// Open the file
	ifstream infile;
	infile.open(filenameIn.c_str());
	
	// Set the number of Nodes in the maze.
	infile >> temp;
	maxNodes = atoi(temp.c_str());
	
	// Sets the name of the first and last node
	infile >> startString;
	infile >> endString;
	
	// Creates an array of the given size
	board = new Node[maxNodes];
	
	// Creates a new node at every index of the array, sets the name of the node, 
	// and sets the index values of the start and end nodes. 
	for (int i = 0; i < maxNodes ; i++)
	{
		infile >> temp;
		board[i] = Node(temp);
		//board[i].setNodeName(temp);
		
		if (temp == startString)
		{
			startNode = i;
		}
		
		if (temp == endString)
		{
			endNode = i;
		}
		
		// Ignore all the directions in this loop
		for (int j = 0; j < directions; j++)
		{
			infile >> temp;
		}
		
	}
	
	infile.close();
	infile.open(filenameIn.c_str());
	
	// Ignore the first three lines
	for (int j = 0; j < 3; j++)
		{
			infile >> temp;
		}
	
	// Links the directional Nodes as well as the
	// SnakeOrLadder Nodes.
	for (int i = 0; i < maxNodes; i++)
	{
		//Name of Node
		infile >> temp;
		
		for (int j = 0; j < directions; j++)
		{
			// Direction
			infile >> temp;
			
			// No Direction, link Null
			if (temp == star)
			{
				if (j == directions - 1)
				{
					board[i].attachSnakeLadderNode(NULL);
				}
				
				else
				{
					board[i].attachNewNode(NULL, j);
				}
			}
			
			// Find index of Direction Node and link
			else
			{
				// Find the index of the Node to link
				for (int k = 0; k < maxNodes; k++)
				{
					nodeName = board[k].getNodeName();
					if (temp == nodeName)
					{
						index = k;
						break;
						
					}
				}
				
				if (j == directions - 1)
				{
					board[i].attachSnakeLadderNode(&board[index]);
				}
				
				else
				{
					board[i].attachNewNode(&board[index], j);
				}
				tempNode = NULL;
				delete tempNode;
			}
		}
			
	}
	
	if (maxNodes == 0) 
	{
		cout << "Maze File either not found or not formatted properly. Exiting Program." << endl;
		exit(1);
	}
	
}
	
// The enterUsers method prompts the user to enter the number of users and their names.
// It creates four arrays that will be used throughout the rest of the game. An array of
// their names, an array of their current node, an array of their moves, and an array 
// of the number of steps they took.
void Game::enterUsers()
{
	nPlayers = 0;
	string dummy, numPlayers, temp;
	cout << "Enter the number of players: ";
	while (nPlayers == 0) 
	{
		cin >> numPlayers;
		getline(cin, dummy);
		nPlayers = atoi(numPlayers.c_str());
		if (nPlayers == 0)
		{
			cout << "Please enter a valid number: " ;
		}
	}
	
	players = new string[nPlayers];
	playerNode = new Node[nPlayers];
	playerMoves = new string[nPlayers];
	playerSteps = new int[nPlayers];
	
	for (int i = 0; i < nPlayers; i++)
	{
		cout << "Enter the Name of Player #";
		cout << i + 1;
		cout << ": ";
		cin >> temp;
		getline (cin, dummy);
		players[i] = temp;	
		playerNode[i] = board[startNode];
		playerMoves[i] = board[startNode].getNodeName();
		playerSteps[i] = 0; 
	}
	
}

// The paths method takes in the current player, finds their current node, 
// and outputs the directions they can take. 
string Game::paths(int player)
{
	int numPaths = 0;
	Node tempNode = playerNode[player];
	map<int, string> myMap;
	string allpaths = "";
	myMap[0] = "North";
	myMap[1] = "East";
	myMap[2] = "South";
	myMap[3] = "West";
	
	for (int i = 0; i < 4; i++)
	{
		if (tempNode.getAttachedNode(i) != NULL)
		{
			if (numPaths != 0)
			{
				allpaths += " or ";
			}
			allpaths += myMap.at(i);
			numPaths++;
		}
	}
	
	if (numPaths == 1)
		allpaths += " only";
	return allpaths;
	
}

// The switchNode method takes in the player and their desired direction and 
// updates their current node, string of moves, and number of steps taken.
void Game::switchNode(int player, int dir)
{
	Node* temp = playerNode[player].getAttachedNode(dir);
	playerNode[player] = *temp;
	playerMoves[player] += " " + playerNode[player].getNodeName();
	playerSteps[player]++;
}

// The snakeOrLadder method takes in the player and jumps to the snake or 
// of their current node. It compares their ending node to their current
// node to determine whether it was a snake or ladder. A snake goes to a lower
// node name while a ladder goes to a higher node name.
void Game::snakeOrLadder(int player)
{
	Node theMove = *playerNode[player].getSnakeLadderNode();
	string starting = playerNode[player].getNodeName();
	string ending = theMove.getNodeName();
	
	if (starting.compare(ending) > 0)
	{
		cout << "and you have taken a snake to ";
	}
	
	else 
	{
		cout << "and you have taken a ladder to ";
	}
	
	cout << ending + ", ";
	playerNode[player] = theMove;
	playerMoves[player] += " " + ending;
}

// The endGame function is called when a player reaches the last Node of the maze. 
// It takes in the player and outputs their name, moves, and steps.
void Game::endGame(int winner)
{
	cout << endl << "Congratulations, " + players[winner] + " is the winner! You have reached the destination point." << endl;
	cout << "You took ";
	cout << playerSteps[winner];
	cout << " steps." << endl << "The steps you visited are: " + playerMoves[winner] << endl;
	exit(1);
	
}

// The move method takes in the player and the amount of turns they have.
// It calls the paths method to find paths, snakeOrLadder method if the players 
// current node has one, and the endGame method if they reach the end.
// It displays their current options to move and prompts for their choice.
void Game::move(int player, int turns)
{
	string name, path, dummy, allpaths;
	bool chosen;
	
	for (int i = 0; i < turns; i++)
	{
		allpaths = paths(player);
		
		
		cout << players[player] + " is currently in Node " + playerNode[player].getNodeName();
		cout << " of the Maze Game, ";
		
		// Loop to catch multiple snakes or ladders in a row
		while (playerNode[player].getSnakeLadderNode() != NULL)
		{
			snakeOrLadder(player);
			allpaths = paths(player);
		}
		
		cout << "you can go " + allpaths + ". What is your choice?" << endl;
		
		chosen = false;
		
		while (!chosen) 
		{
			cin >> path;
			getline(cin, dummy);
			if (path == "")
				path = "Z";
			
			
			if (path == "N" && allpaths.find("N") != string::npos)
			{
				switchNode(player, 0);
				chosen = true;
			}
			
			else if (path == "E" && allpaths.find("E") != string::npos)
			{
				switchNode(player, 1);
				chosen = true;
			}
			
			else if (path == "S" && allpaths.find("S") != string::npos)
			{
				switchNode(player, 2);
				chosen = true;
			}
			
			else if (path == "W" && allpaths.find("W") != string::npos)
			{
				switchNode(player, 3);
				chosen = true;
			}
			
			else
			{
				cout << "Please enter a valid direction in proper format (N, E, W, or S): " + allpaths << endl;
			}
		}
		
		if (playerNode[player].getNodeName() == board[endNode].getNodeName())
		{
			endGame(player);
		}
	}
}

// The turn method outputs the current player's turn and gives them a random number of
// moves between 1 and 6. It calls the move function with the current player and their
// number of moves.
void Game::turn(int whose_turn)
{
	string name, dummy;
	srand(time(0));
	int turns = rand() % 6 + 1;
	name = players[whose_turn];
	
	string message = name + "'s turn";
	
	string bars(21, '=');
	int numSpaces = 0;
	string vbar = "|";
	
	numSpaces = bars.size() - message.size() - 2*vbar.size();
	string spaces(numSpaces/2, ' ');
	message = vbar + spaces + message + spaces;
	if (numSpaces%2 != 0)
		message += " ";
	message += vbar;
	
	cout << endl;
	cout << bars;
	cout << endl << message;
	cout << endl << bars << endl << endl;
	
	cout << name + "'s turn to throw the dice, just hit enter";
	getline(cin, dummy);
	cout << name + "'s dice throw is ";
	cout << turns;
	cout << endl << name + " can move to ";
	cout << turns;
	cout << " nodes" << endl << endl;
	move(whose_turn, turns);
}

// The runGame method displays the game banner and calls turn with the given player
// in an infinite loop. the program exits when endGame is called.
void Game::runGame()
{
	cout << "=====================================================" << endl;
	cout << "|    Welcome to the Snakes and Ladders Maze Game    |" << endl;
	cout << "=====================================================" << endl << endl;
	enterUsers();
	while (1 != 2)
	{
		for (int i = 0; i < nPlayers; i++)
		{
			turn(i);
		}
		
	}
	
}