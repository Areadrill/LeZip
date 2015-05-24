#include <string>
#include <vector>

using namespace std;

class LZWDic{
	vector<string> strings;
	//vector<int> codes;

public:
	LZWDic();
	string getString(int code);
	int getCode(string str);
	int addString(string str);
	int editString(int code, string str);
	void show();
};



