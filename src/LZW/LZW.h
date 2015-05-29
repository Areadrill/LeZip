#include <string>

int encode(std::string filename, string outfile="out.txt.lzw");
vector<bool> makeBinary(int num, LZWDic *dic);
int decode(std::string filename);
