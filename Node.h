#include <iostream>
// Program 3:	tjr0023_3
// Name: 		Tyler Robins
// Class: 		COMP 2710 Section 1
// Date:		11/18/2017
// Email:		tjr0023@auburn.edu
//
// Description: This is the header file for the Node program. 
//              It contains all of the variables and functions of the Node program.
//
using namespace std;


class Node
{
public:
    Node(string newname);
    Node();
    void setNodeName(string newname);
    string getNodeName();
    void attachNewNode(Node *newNode, int direction);
    Node* getAttachedNode(int direction);
    void attachSnakeLadderNode(Node *newNode);
    Node* getSnakeLadderNode();

private:
    string name;
    Node* attachedNodes[4];
    Node* snakeOrLadderNodes;
};