#include <iostream>
#include "LZWDic.h"
#include <fstream>

using namespace std;


int encode(string filename, LZWDic *dic){
	ifstream file;
	file.open(filename.c_str());
	string temp;
	string str = " ";

	while(getline(file, temp)){
		for(int i = 0; i < temp.size(); i++){
			int it = 0;
			str.at(it++) = temp.c_str()[i];
			while(dic->getCode(str) != -1){ //ja existe no dicionario
				str.at(it++) = temp.c_str[++i];
			}
			dic->addString(str);
			str = " ";
			it = 0;
		}
	}

}
