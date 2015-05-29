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

int encode(string filename,  string outfile="out.txt.lzw"){
	/*ifstream inFile(filename.c_str());
	stringstream outName;
	outName << filename << ".lzw";
	ofstream outFile(outName.str().c_str(), (ios::out|ios::binary));
	bitstream test = bitstream(outFile);
	bool stop = 0;

	if(!inFile.is_open()){
		cout << "Input file didnt open";
		return -1;
	}
	if(!outFile.is_open()){
		cout << "Output file didnt open";
		return -1;
	}
*/



	map<string, int> dictionary;
	for(int c = 0; c < 256; c++)
	{
		string s = "";
		s.push_back(c);
		dictionary.insert(pair<string, int>(s,(int)c));
		cout << (int)c << endl;
	}

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
		next = next-1;
	}

	/*string temp;
	ostringstream string;
	while(getline(inFile, temp)){
		int j;
		for(int i = 0; i < temp.size(); i++){
			j = 1;
			string << temp.at(i);
			while(dic->getCode(string.str()) != -1){ //ja existe no dicionario
				if(i+j >= temp.size()){
					break;
				}
				string << temp.at(i+j);
				j++;
			}
			if(j > 1){
				i += j-2;
			}

			//send to file
			std::string fromStream = "                                                                                           ";

			if(string.str().size() != 1){
				fromStream.resize(string.str().size()-1, '\0');
				for(int i = 0; i < strlen(string.str().c_str())-1; i++){
					fromStream.at(i) = string.str().at(i);
				}

			}
			else{
				fromStream.resize(string.str().size(), '\0');
				for(int i = 0; i < strlen(string.str().c_str()); i++){
					fromStream.at(i) = string.str().at(i);
				}
				stop = 1;
			}



			//cout << fromStream << endl << string.str() << endl << endl;

			int code = dic->getCode(fromStream);
			if(code == -1){
				cout << "fdeu\n";
				outFile.close();
				return -1;
			}


			vector<int> bits = makeBinary(code, dic);
			for(int i = 0; i < dic->getBitNum();i++){
				test << bits.front();
				//cout << bits.front();
				bits.erase(bits.begin());
			}
			cout << "added " << string.str() << std::endl;
			dic->addString(string.str());

			string.str("");

			if(stop){
				break;
			}
		}
	}
	test.flush();
	cout << "finished" << endl;
	outFile.close();*/
	return 0;
}



int decode(string filename){

	LZWDic dic = LZWDic();


	ifstream compressed(filename.c_str(), ios::in|ios::binary);
	if(!compressed.is_open()){
		return -1;
	}
	ofstream decompressed("decompressed.txt");
	if(!decompressed.is_open()){
		return -1;
	}

	char *testByte = new char[1];
	vector<int> bits;

	while(compressed){
		compressed.read(testByte, 1);


		if(bits.size() < dic.getBitNum()){

		}
		compressed.read(testByte, 1);
		//cout << testByte << endl;
		//getCodeFromBin('a');
	}
	compressed.clear();
}
