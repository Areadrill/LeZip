#include "LZWDic.h"
#include <iostream>
#include <cmath>


LZWDic::LZWDic(){
	for(int i = 0; i <= 255; i++){
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

void LZWDic::show(){
	for(int i = 0; i < strings.size(); i++){
		cout << strings.at(i) << endl;
	}
}

int LZWDic::getBitNum(){
	int power = 0;

	while(pow(2, power) < this->strings.size()){
		power++;
	}

	return power;
}
