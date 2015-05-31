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

int huffmanEncode(std::string infile, std::string outfile){
	std::ofstream ofile(outfile, std::ofstream::binary | std::ofstream::trunc);
	std::ifstream ifile(infile, std::ofstream::binary);
	if(!ofile.is_open() || !ifile.is_open()){
		return -1;
	}
	HuffmanTree huf(ifile);
	huf.encode(ifile, ofile);
	ifile.close();
	ofile.close();
	return 0;
}

int huffmanDecode(std::string infile, std::string outfile){
	std::ofstream ofile(outfile, std::ofstream::binary | std::ofstream::trunc);
	std::ifstream ifile(infile, std::ofstream::binary);
	if(!ofile.is_open() || !ifile.is_open()){
			return -1;
	}
	HuffmanTree::decode(ifile, ofile);
	ofile.close();
	ifile.close();
	return 0;
}

