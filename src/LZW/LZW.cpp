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


vector<int> makeBinary(int num, LZWDic *dic){
	int bitNum = dic->getBitNum();
	cout << bitNum << endl;
	int sum = 0;

	vector<int> bits;

	int power = bitNum;
	while((sum != num) || power >= 0){
		if(pow(2, power) > num-sum){
			bits.push_back(0);
		}
		else{
			bits.push_back(1);
			sum += pow(2, power);
		}
		power--;
	}
	return bits;
}

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
			cout << (int)c << endl;
		}
}
int encode(string filename,  string outfile="out.txt.lzw"){

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
		dictionary.insert(pair<string, int>(currentString, dictionary.size()));
		curr = next-1;
		next = curr+1;
	}


	return 0;
}



int decode(string filename, string outputfile){
	map<string, int> dictionary;
	initDic(dictionary);

	ifstream ifile(filename.c_str());
	ofstream ofile(outputfile);
	if(!ifile.is_open() || !ofile.is_open())
		return -1;



}
