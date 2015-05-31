#pragma once
#include <queue>
#include <iostream>
#include <map>
#include <fstream>
#include "INode.h"

class HuffmanTree {
private:
	std::priority_queue<INode*, std::vector<INode*>, pless<INode> > queue;
	std::map<char, std::queue<bool> > codecache;
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


int huffmanEncode(std::string infile, std::string outfile);
int huffmanDecode(std::string infile, std::string outfile);
