#include "Node.h"
// Program 4:	tjr0023_3
// Name: 		Tyler Robins
// Class: 		COMP 2710 Section 1
// Date:		11/18/2017
// Email:		tjr0023@auburn.edu
//
// Description: This is the Node file. This Node program is specifically 
//              made for the Maze Game. The Nodes have names, directional
//              attached nodes, and an attached snakeOrLadder node.
//

// Node() is the constructor for the node class. It sets all attached nodes to null.
Node::Node()
{
    attachedNodes[0] = NULL;
    attachedNodes[1] = NULL;
    attachedNodes[2] = NULL;
    attachedNodes[3] = NULL;
    snakeOrLadderNodes = NULL;
}

// Additional constructor to set the node name during creation.
Node::Node(string newname)
{
    name = newname;
    attachedNodes[0] = NULL;
    attachedNodes[1] = NULL;
    attachedNodes[2] = NULL;
    attachedNodes[3] = NULL;
    snakeOrLadderNodes = NULL;
}

// Method to set the node name
void Node::setNodeName(string newname)
{
    name = newname;
}

// Method to get the node name
string Node::getNodeName()
{
    return name;
}

// Method to attach a directional node. Takes in a pointer to
// the node to be attached and the int value of the direction
// to set it to.
void Node::attachNewNode(Node *newNode, int direction)
{
    attachedNodes[direction] = newNode;
}

// Method to return the attached node of the desired direction.
Node* Node::getAttachedNode(int direction)
{
    return attachedNodes[direction];
}

// Method to set a snakeOrLadder node. Takes in a pointer node.
void Node::attachSnakeLadderNode(Node *newNode)
{
    snakeOrLadderNodes = newNode;
}

// Method to return the snakeOrLadder node.
Node* Node::getSnakeLadderNode()
{
    return snakeOrLadderNodes;
}