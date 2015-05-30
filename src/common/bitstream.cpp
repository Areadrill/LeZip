#include "bitstream.h"

void bitstream::operator<<(const bool rhs){

	this->queue.push(rhs);
	if (this->queue.size() == 8)
		flush();
}


void bitstream::flush(){
	char toFlush = 0;
	for(int i = 0; i < 8; i++){
		bool bit;
		if (queue.empty())
			bit = false;
		else{
			bit = queue.front();
			queue.pop();
		}
		toFlush <<= 1;
		toFlush |= bit;
	}
	this->out << toFlush;
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
