#include <iostream>
#include <fstream>
#include <sstream>

#include "bitstream.h"
#include "../LZW/LZWDic.h"
#include "../LZW/LZW.h"
#include "../Huffman/HuffmanTree.h"
#include "../Huffman/INode.h"

using namespace std;

int main(int argc, char **argv){
	/*string ola = "olooaa";
	stringstream stream(ola);
	HuffmanTree tree = HuffmanTree(stream);
	cout << "done";
	bitstream str = bitstream(cout);
	str << 0;
	str << 0;
	str << 1;
	str << 1;
	str << 0;
	str << 0;
	str << 0;
	str << 0;*/

	LZWDic dic = LZWDic();
	//cout << dic.getBitNum() << endl;


	encode("lusiadas.txt", "escrevamlusiadas.txt.lzw");
	decode("escrevamlusiadas.txt.lzw", "ja me lembrei ja me esqueci.txt");

	/*int bits = dic.getBitNum();
	cout << bits << endl;*/
}
