#include "LZWDic.h"
#include <iostream>


LZWDic::LZWDic(){
	for(int i = 32; i <= 126; i++){
		string str = " ";
		str.at(0) = (char)i;
		this->addString(str);
	}
}


string LZWDic::getString(int code){
	return strings.at(code);
}

int LZWDic::getCode(string str){
	for(int i = 0; i < strings.size(); i++){
		if(strings.at(i) == str){
			return i;
		}
	}
	return -1;
}

int LZWDic::addString(string str){
	strings.push_back(str);
	return strings.size()-1;
}

int LZWDic::editString(int code, string str){
	strings.at(code) = str;
	return code;
}
