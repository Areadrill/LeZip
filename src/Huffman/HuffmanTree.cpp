#include "HuffmanTree.h"
#include "INode.h"

HuffmanTree::HuffmanTree(std::istream &is) {
	initQueue(is);
	buildTree();
}

void HuffmanTree::initQueue(std::istream &is){
	std::map<char, int> dictionary;
	char read;
	is >> std::noskipws >> read;
	while(!is.eof()){
		if (dictionary.find(read) == dictionary.end())
			dictionary[read] = 1;
		else
			dictionary[read] = dictionary[read] +1;
		is >> read;
		std::cout << read;
	}
	std::map<char,int>::const_iterator it;
	for(it = dictionary.begin(); it != dictionary.end(); it++)
	{
		LeafNode *leaf = new LeafNode(it->first, it->second);
		this->queue.push(leaf);
	}
}

void HuffmanTree::buildTree(){
	while(this->queue.size() > 1){
		INode* left = queue.top();queue.pop();
		INode* right = queue.top();queue.pop();
		left->printValue(); right->printValue();
		Node* newNode = new Node(left, right);
		queue.push(newNode);
	}
	this->root = queue.top();
	queue.pop();
}

void HuffmanTree::encode(std::istream &is, std::ostream &os){
	bitstream bit = bitstream(os);
	is.clear();
	is.seekg(0);

	while (!is.eof()){
		char read;
		is >> std::noskipws >> read;

		this->root->encodeChar(read, bit);
	}
	bit.flush();
}
