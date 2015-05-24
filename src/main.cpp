#include <iostream>
#include "LZWDic.h"
#include "LZW.h"

using namespace std;

int main(){
	LZWDic testDic = LZWDic();
	cout << "Encoding\n";
	encode("test.txt", &testDic);
	cout << "Showing\n";
	testDic.show();

}
