/*
 * HuffmanTree.h
 *
 *  Created on: May 21, 2015
 *      Author: up201304395
 */

#ifndef HUFFMANTREE_H_
#define HUFFMANTREE_H_

#include <queue>
#include <iostream>
#include "INode.h"

class HuffmanTree {
private:
	std::priority_queue<INode*> queue;
	INode* root;
	void initQueue(std::istream &is);
	void buildTree();
public:
	void encode(std::istream &is, std::ostream &os);

public:
	HuffmanTree(std::istream &is);

};

#endif /* HUFFMANTREE_H_ */
