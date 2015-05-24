#include <bitset>
#include "bitstream.h"

void bitstream::operator<<(bool rhs){
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
