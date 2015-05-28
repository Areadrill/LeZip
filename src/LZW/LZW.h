#include <string>

int encode(std::string filename, LZWDic *dic);
vector<bool> makeBinary(int num, LZWDic *dic);
int decode(std::string filename);
