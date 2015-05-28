/*
 * INode.h
 *
 *  Created on: May 21, 2015
 *      Author: up201304395
 */

#pragma once
#include "common/bitstream.h"
class INode {
protected:
	int frequency;
public:
	int getFrequency(){return frequency;};
	INode(int frequency);
	INode(){this->frequency = 0;};
	bool operator< ( const INode &rhs) const;
	virtual void encodeChar (const char c, bitstream &bit, std::string prefix = "") = 0;
	virtual ~INode() = 0;
	virtual void printValue() = 0;
};

class Node: public INode{
private:
	INode* left;
	INode* right;
public:
	Node(INode* left, INode* right);
	~Node(){delete left; delete right;};
	void encodeChar (const char c, bitstream &bit, std::string prefix = "");
	void printValue(){};
};
class LeafNode: public INode{
private:
	char value;
public:
	LeafNode(char value, int frequency);
	void encodeChar (const char c, bitstream &bit, std::string prefix = "");
	~LeafNode(){};
	void printValue(){std::cout << value;};
};

template<typename Type, typename Compare = std::less<Type> >
struct nodeless : public std::binary_function<Type*, Type*, bool> {
	bool operator()(const Type* lhs, const Type* rhs) const
	{
		return Compare()(*lhs, *rhs);
	}
}

