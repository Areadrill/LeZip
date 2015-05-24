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
	return (this->frequency < rhs.frequency);
}

Node::Node(INode left, INode right){
	this->left = left;
	this->right = right;
	this->frequency = this->left.getFrequency() + this->right.getFrequency();
}

LeafNode::LeafNode(char value, int frequency):INode(frequency){
	this->value = value;
}


int main(){
	std::string ola = "olooaa";
	std::stringstream stream(ola);
	HuffmanTree tree = HuffmanTree(stream);
	std::cout << "done";
	bitstream str = bitstream(std::cout);
	str << 0;
	str << 0;
	str << 0;
	str << 0;
	str << 1;
	str << 0;
	str << 0;
	str << 0;
}
