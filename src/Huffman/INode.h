/*
 * INode.h
 *
 *  Created on: May 21, 2015
 *      Author: up201304395
 */

#pragma once

class INode {
protected:
	int frequency;
public:
	int getFrequency(){return frequency;};
	INode(int frequency);
	INode(){this->frequency = 0;};
	bool operator< ( const INode &rhs) const;
};

class Node: public INode{
private:
	INode left;
	INode right;
public:
	Node(INode left, INode right);

};
class LeafNode: public INode{
private:
	char value;
public:
	LeafNode(char value, int frequency);
};


