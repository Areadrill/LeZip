/*
 * bistream.h
 *
 *  Created on: 24 May 2015
 */

#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <vector>
#include <bitset>

class bitstream {
private:
	std::queue<bool> queue;
	std::ostream &out;
public:
	bitstream(std::ostream &os):out(os){};
	void operator<<(const bool rhs);
	void operator<<(const char rhs);
	void flush();
};



