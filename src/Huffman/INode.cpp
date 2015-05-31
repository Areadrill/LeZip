#include "INode.h"
#include "HuffmanTree.h"

#include <fstream>
INode::INode(int frequency) {
	this->frequency = frequency;
}

 bool INode::operator<(const INode &rhs) const{
	return (this->frequency > rhs.frequency);
}


INode* INode::read(std::queue<bool> &bits){
	INode* result;

	bool read = bits.front();

	bits.pop();
	if (read){

		char value = 0x00;
		for (int i = 7; i >= 0; i--)
		{
			char bit = bits.front();
			bits.pop();
			bit <<= i;
			value |= bit;
		}

		result = new LeafNode(value,0);
	}
	else{

		result = new Node(INode::read(bits), INode::read(bits));

	}
	return result;
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
void Node::saveNode(bitstream & os){
	os << false;
	//std::cout << "0";
	this->left->saveNode(os);
	this->right->saveNode(os);

}

char Node::decodeValue(std::queue<bool> &bits){
	if(bits.empty())
		return 'x';
	//std::cout << "decoding middle node" << bits.front() <<std::endl;
	bool current = bits.front();
	bits.pop();
	if (!current)
		return this->right->decodeValue(bits);
	else
		return this->left->decodeValue(bits);
}

LeafNode::LeafNode(char value, int frequency):INode(frequency){
	this->value = value;

}

void LeafNode::encodeChar(const char c, bitstream &bit, std::string prefix){
	if(this->value != c)
		return;
	//std::cout << "coding " << this->value << std::endl;
	for(unsigned int i = 0; i < prefix.size();i++)
	{
		bool value = prefix.at(i) == '0' ? true : false;
		bit << value;
		//std::cout << "inserting " << value << std::endl;
	}



}

void LeafNode::saveNode(bitstream &os){
	os << true;
	for (int i = 0; i < 8; i++){
		char extractor = 0x80;
		char copy = this->value << i;
		bool bit = extractor & copy;
		os << bit;
	}
	//std::cout << "1" << this->value;
}

char LeafNode::decodeValue(std::queue<bool> &bits){
	//std::cout << "decoding " << this->value << std::endl;
	return this->value;

}
