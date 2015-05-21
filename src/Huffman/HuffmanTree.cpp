/*
 * HuffmanTree.cpp
 *
 *  Created on: May 21, 2015
 *      Author: up201304395
 */
#include <map>
#include "HuffmanTree.h"
#include "INode.h"

HuffmanTree::HuffmanTree(std::istream &is) {
	initQueue(is);
	buildTree();
}

void HuffmanTree::initQueue(std::istream &is){
	std::map<char, int> dictionary;
	char read;
	is >> read;
	while(!is.eof()){
		if (dictionary.find(read) == dictionary.end())
			dictionary[read] = 1;
		else
			dictionary[read] = dictionary[read] +1;
		is >> read;
	}
	std::map<char,int>::const_iterator it;
	for(it = dictionary.begin(); it != dictionary.end(); it++)
	{
		LeafNode leaf = LeafNode(it->first, it->second);
		this->queue.push(leaf);
	}
}

void HuffmanTree::buildTree(){
	while(this->queue.size() > 1){
		INode left = queue.top();queue.pop();
		INode right = queue.top();queue.pop();
		Node newNode = Node(left, right);
		queue.push(newNode);
	}
	this->root = queue.top();
	queue.pop();
}
