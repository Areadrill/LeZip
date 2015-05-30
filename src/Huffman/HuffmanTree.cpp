#include "HuffmanTree.h"
#include "INode.h"
#include <iomanip>
#include <fstream>

HuffmanTree::HuffmanTree(std::istream &is) {
	initQueue(is);
	buildTree();
}

void HuffmanTree::initQueue(std::istream &is){
	std::map<char, int> dictionary;
	char read;

	while(is >> std::noskipws >> read){
		if (dictionary.find(read) == dictionary.end())
			dictionary[read] = 1;
		else
			dictionary[read] = dictionary[read] +1;


	}
	for(std::map<char, int >::const_iterator it = dictionary.begin();
	    it != dictionary.end(); ++it)
	{
	    std::cout << it->first << " " << it->second << " " << it->second << "\n";
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
		std::ofstream out;
		//left->printValue(); right->printValue();
		Node* newNode = new Node(left, right);
		queue.push(newNode);
	}
	this->root = queue.top();
	queue.pop();
}


std::queue<bool> streamToQueue(std::istream &is){
	std::queue<bool> result;
	std::istreambuf_iterator<char> eos;
	std::string s(std::istreambuf_iterator<char>(is), eos);
	char extractor = 0x80;
	char read;
	for(unsigned int i = 0; i < s.size(); i++){
		read = s.at(i);
		for (int i = 0; i <8; i++)
		{
			char in = extractor & read;
			bool bit = !in ? false : true;
			result.push(bit);
			read <<= 1;
		}
	}
	return result;
}

void HuffmanTree::saveTree(bitstream &bit){
	this->root->saveNode(bit);
}

HuffmanTree HuffmanTree::loadTree(std::queue<bool> &bits){
	return HuffmanTree(INode::read(bits));
}

void HuffmanTree::encode(std::istream &is, std::ostream &os){
	bitstream bit = bitstream(os);
	is.clear();
	is.seekg(0);
	this->saveTree(bit);
	char read;
	while (is >> std::noskipws >> read){
		//std::cout << "gonna incode " << read << std::endl;
		this->root->encodeChar(read, bit);
	}
	bit.flush();
}

void HuffmanTree::decode(std::istream &is, std::ostream &os){
	std::queue<bool> bits = streamToQueue(is);
	HuffmanTree huff = HuffmanTree::loadTree(bits);

	while(!bits.empty()){

		os << huff.root->decodeValue(bits);

	}


}

