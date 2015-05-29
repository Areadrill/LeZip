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
#include <map>
#include "INode.h"

class HuffmanTree {
private:
	std::priority_queue<INode*, std::vector<INode*>, pless<INode> > queue;
	INode* root;
	void initQueue(std::istream &is);
	void buildTree();

public:
	HuffmanTree(std::istream &is);
	HuffmanTree(INode* root):root(root){};
	~HuffmanTree(){delete root;};
	void encode(std::istream &is, std::ostream &os);
	void saveTree(bitstream &bit);
	static HuffmanTree loadTree(std::queue<bool> &bits);
	static void decode(std::istream &is, std::ostream &os);

};
std::queue<bool> streamToQueue(std::istream &is);


#endif /* HUFFMANTREE_H_ */
