#include <iostream>
#include "LZWDic.h"
#include "../common/bitstream.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <bitset>
#include <cstring>
#include <map>
#include <string>

using namespace std;

void lzwWrite(int number, bitstream &bit, int max){
	int size = ceil(log2(max));
	char extractor = 0x01;
	for (int i = size-1; i >= 0; i--){
		bool bits = (extractor << i) & number;
		bit << bits;
	}
}
void initDic(map<string, int> &dic){
	for(int c = 0; c < 256; c++)
		{
			string s = "";
			s.push_back(c);
			dic.insert(pair<string, int>(s,(int)c));
		}
}
int LZWencode(string filename,  string outfile="out.txt.lzw"){

	map<string, int> dictionary;
	initDic(dictionary);

	ifstream infile;
	infile.open(filename.c_str(), ifstream::binary);
	if (!infile.is_open())
		return -1;
	ofstream ofile;
	ofile.open(outfile.c_str(), ofstream::trunc | ofstream::binary);
	bitstream bit = bitstream(ofile);


	istreambuf_iterator<char> eos;
	string s = string(istreambuf_iterator<char>(infile), eos);
	unsigned int curr = 0;
	unsigned int next = 1;
	while(curr < s.size()){
		string currentString = string(s.begin()+curr, s.begin()+next);
		while (dictionary.find(currentString) != dictionary.end()){
			next++;
			currentString = string(s.begin()+curr, s.begin()+next);
		}
		string out = string(s.begin()+curr, s.begin()+next-1);
		lzwWrite(dictionary.find(out)->second, bit, dictionary.size());
		cout << "adding " << currentString << " with size " << currentString.size() << endl;
		dictionary.insert(pair<string, int>(currentString, dictionary.size()));
		curr = next-1;
		next = curr+1;
	}

	cout << "done\n";
	bit.flush();
	return 0;
}

int getNextCode(std::queue<bool> &bits, int currentBits){
	int code = 0x0000;
	for(int i = currentBits-1; i >= 0; i--){
		if(bits.empty())
		return 0;
		int extracted = bits.front();bits.pop();
		code |= (extracted << i);
	}
	cout << "code:" << code << endl;
	return code;
}

int LZWdecode(string filename, string outputfile){
	map<int, string> dic;
	for(int i = 0; i < 256; i++){
		string s = "";
		s.push_back((char)i);
		dic.insert(pair<int,string>(i,s));
	}
	ifstream ifile(filename.c_str(), ifstream::binary);
	ofstream ofile(outputfile.c_str(), ofstream::binary);
	if(!ifile.is_open() || !ofile.is_open())
		return -1;

	queue<bool> bits;
	bits = streamToQueue(ifile);
	int x = 1;
	string s="", temp="";

	int code = getNextCode(bits, 8);
	s = dic.find(code)->second;
	ofile << s;

	while(!bits.empty()){
		int currentBits = ceil(log2(dic.size()+1));
		x=0;
		code = getNextCode(bits, currentBits);

		if(dic.find(code) != dic.end()){
			cout << "encontrou"<< dic.find(code)->second << endl;
			temp = s;
			s = dic.find(code)->second;

			string newEntry = 	temp;
			newEntry.push_back(s[0]);
			cout << "added " << newEntry << endl;
			dic.insert(pair<int, string>(dic.size(), newEntry));
		}
		else{
			cout << "nao encontrou" << endl;
			string newEntry = s;
			newEntry.push_back(s.at(0));
			cout << "added " << newEntry << endl;
			dic.insert(pair<int, string>(dic.size(), newEntry));
			s = dic.find(code)->second;
		}
		ofile << s;
		cout << currentBits << endl;
	}
}
