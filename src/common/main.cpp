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
	encode("Copy of lusiadas.txt", "escrevamlusiadas.txt.lzw");
	decode("escrevamlusiadas.txt.lzw", "traçocantosexto.txt");
}

