/*
 * INode.cpp
 *
 *  Created on: May 21, 2015
 *      Author: up201304395
 */

#include "INode.h"
#include "HuffmanTree.h"
#include "../common/bitstream.h"
#include <sstream>
INode::INode(int frequency) {
	this->frequency = frequency;
}

 bool INode::operator<(const INode &rhs) const{
	return (this->frequency > rhs.frequency);
}
INode::~INode(){}

Node::Node(INode *left, INode *right){
	this->left = left;
	this->right = right;
	this->frequency = this->left->getFrequency() + this->right->getFrequency();
}
void Node::encodeChar(const char c, bitstream &bit, std::string prefix){
	std::string codeleft = prefix;codeleft.append("0");
	std::string coderight = prefix;coderight.append("1");
	this->left->encodeChar(c, bit, codeleft);
	this->right->encodeChar(c, bit, coderight);
	//std::cout << "middle node with code " << prefix << std::endl;
}

LeafNode::LeafNode(char value, int frequency):INode(frequency){
	this->value = value;
}

void LeafNode::encodeChar(const char c, bitstream &bit, std::string prefix){
	if(this->value != c)
		return;
	std::cout << "matched " << this->value << " to prefix " << prefix << std::endl;
	for(unsigned int i = 0; i < prefix.size();i++)
	{
		bool value = prefix.at(i) == '0' ? true : false;
		bit << value;
	}

}



int main(){
	std::string ola = "oloooa";
	std::stringstream stream(ola);
	HuffmanTree tree = HuffmanTree(stream);
	tree.encode(stream, std::cout);
}
