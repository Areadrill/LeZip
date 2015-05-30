#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>

#include "bitstream.h"
#include "../LZW/LZWDic.h"
#include "../LZW/LZW.h"
#include "../Huffman/HuffmanTree.h"
#include "../Huffman/INode.h"

using namespace std;

void printUsage(string name){
	cout << "Usage: \n\tCompression: " << name << " -c [compression algorithm] [directory]" << endl;
	cout << "\tDecompression: " << name << " -d [directory]" << endl;
	cout << "For more information use " << name << " --help" << endl;
}

void printTutorial(){
	cout << "Available operations: \n" << "\t-c: compress\n\t-d: decompress" << endl;
	cout << "\nAvailable algorithms: \n" << "\t-huff: Huffman\n\t-lzw: Lempel-Ziv-Welch\n\t-rle: Run Length Encoding" << endl;
}


int compress(DIR *dir, string srcDir, string alg, string name){

	string destDir = srcDir;
	destDir.append(".comp");
	mkdir(destDir.c_str());

	struct dirent *foldEnt;
	while((foldEnt = readdir(dir)) != NULL){
		if(foldEnt->d_type == 0){
			string fileName = srcDir;
			fileName.append("/");
			fileName.append(foldEnt->d_name);

			string fileName2 = destDir;
			fileName2.append("/");
			fileName2.append(foldEnt->d_name);
			fileName2.append(".lzw");

			if(alg == "-huff"){
				//huffencode
			}
			else if(alg == "-lzw"){
				LZWencode(fileName, fileName2);
			}
			else if(alg == "-rle"){
				//rleEncode
			}
			else{
				printUsage(name);
				return -1;
			}
		}
	}
	return 1;
}

int decompress(DIR *dir, string srcDir){
	string destDir = string(srcDir.begin(), srcDir.end()-5);
	mkdir(destDir.c_str());
	struct dirent *foldEnt;

	while((foldEnt = readdir(dir)) != NULL){
		string fileName = srcDir;
		fileName.append("/");
		fileName.append(foldEnt->d_name);

		string fileName2 = destDir;
		fileName2.append("/");

		cout << fileName << endl << fileName2 << endl;

		if(foldEnt->d_type == 0){
			for(int i = strlen(foldEnt->d_name); i > 0; i--){

				if(foldEnt->d_name[i] == '.'){
					if(i == strlen(foldEnt->d_name)-5){
						//huffdecode
						break;
					}
					else if(i == strlen(foldEnt->d_name) - 4){
						if(foldEnt->d_name[i+1] == 'l'){
							fileName2.append(foldEnt->d_name);
							fileName2.at(fileName2.size()-3) = '\0';
							cout << fileName2 << endl;

							LZWdecode(fileName, fileName2);
							break;
						}
						else if(foldEnt->d_name[i+1] == 'r'){
							//rleDecode
							break;
						}
					}
				}
			}
		}
	}
}

int main(int argc, char **argv){

	if(argc < 2){
		printUsage(argv[0]);
		return -1;
	}
	else if(argc != 4 && !strcmp(argv[1], "-c")){
		printUsage(argv[0]);
		return -1;
	}
	else if(argc != 3 && !strcmp(argv[1], "-d")){
		printUsage(argv[0]);
		return -1;
	}
	else if(argc == 2 && !strcmp(argv[1], "--help")){
		printTutorial();
		return 0;
	}



	DIR *dir;
	if(!strcmp(argv[1], "-c")){
		dir = opendir(argv[3]);
	}
	else if(!strcmp(argv[1], "-d")){
		dir = opendir(argv[2]);
	}
	else{
		cout << "Error: Unnkown operation\n";
		printUsage(argv[0]);
		return -1;
	}
	if(dir == NULL){
		cout << "Error: directory not found\n";
		return -1;
	}

	if(!strcmp(argv[1], "-c"))
		compress(dir, argv[3], argv[2], argv[0]);
	else if(!strcmp(argv[1], "-d"))
		decompress(dir, argv[2]);
	else
		printUsage(argv[0]);

}

