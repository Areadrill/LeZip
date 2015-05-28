#include <iostream>
#include "LZWDic.h"
#include "../common/bitstream.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <bitset>
#include <string.h>

using namespace std;


vector<bool> makeBinary(int num, LZWDic *dic){
	int bitNum = dic->getBitNum();
	int sum = 0;

	vector<bool> bits;

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


int encode(string filename, LZWDic *dic){
	ifstream inFile(filename.c_str());
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

	string temp;
	stringstream string;
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
			dic->addString(string.str());

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


			vector<bool> bits = makeBinary(code, dic);
			for(int i = 0; i < dic->getBitNum();i++){
				test << bits.front();
				bits.pop_back();
			}

			string.str("");

			if(stop){
				break;
			}
		}
	}
	cout << "finished" << endl;
	outFile.close();
	return 0;
}


int decode(string filename){

}
