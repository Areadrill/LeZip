#include <iostream>
#include "LZWDic.h"
#include <fstream>
#include <sstream>

using namespace std;


int encode(string filename, LZWDic *dic){
	ifstream file(filename.c_str());
	if(!file.is_open()){
		cout << "File didnt open";
	}

	string temp;
	stringstream string;
	while(getline(file, temp)){
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
			string.str("");
		}
	}
	return 0;
}


int decode(string filename){

}
