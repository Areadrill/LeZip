#include "bitstream.h"

void bitstream::operator<<(const bool rhs){

	this->queue.push(rhs);
	if (this->queue.size() == 8)
		flush();
}

void bitstream::operator<<(const char rhs){
	char copy = rhs;
	for (int i = 0; i < 8; i++)
	{
		char extractor = 0x0001;
		char in = extractor & copy;
		copy <<= 1;
		if (queue.size() < 8)
			this->queue.push(in);
		if (queue.size() == 8){
			this->flush();
			queue.push(in);
		}
	}
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

