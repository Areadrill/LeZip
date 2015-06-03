#ifdef __unix__
#include <sys/stat.h>
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <string.h>
//#include <chrono>

#include "bitstream.h"
#include "../LZW/LZW.h"
#include "../Huffman/HuffmanTree.h"
#include "../Huffman/INode.h"
#include "../RLE/RLE.h"

using namespace std;
//using namespace std::chrono;


void printUsage(string name){
	cout << "Usage: \n\tCompression: " << name << " -c [compression algorithm] [directory]" << endl;
	cout << "\tDecompression: " << name << " -d [directory]" << endl;
	cout << "For more information use " << name << " --help" << endl;
}

void printTutorial(){
	cout << "Available operations: \n" << "\t-c: compress\n\t-d: decompress" << endl;
	cout << "\nAvailable algorithms: \n" << "\t-huff: Huffman\n\t-lzw: Lempel-Ziv-Welch\n\t-rle: Run Length Encoding" << endl;
}


int compress(DIR *dir, string srcDir, string destDir, string alg, string name){

#ifdef __unix__
	mkdir(destDir.c_str(), 0777);
#else
	mkdir(destDir.c_str());
#endif


	struct dirent *foldEnt;
	while((foldEnt = readdir(dir)) != NULL){
		if(foldEnt->d_type == 8){
			string fileName = srcDir;
			fileName.append("/");
			fileName.append(foldEnt->d_name);

			string fileName2 = destDir;
			fileName2.append("/");
			fileName2.append(foldEnt->d_name);


			if(alg == "-huff"){
				fileName2.append(".huff");
				if(huffmanEncode(fileName, fileName2)){
					cout << "erro ao abrir o ficheiro pretendido" << endl;
					return -1;
				}
			}
			else if(alg == "-lzw"){
				fileName2.append(".lzw");
				LZWencode(fileName, fileName2);
			}
			else if(alg == "-rle"){
				fileName2.append(".rle");
				rlecompress(fileName.c_str(), fileName2.c_str());
				//rleEncode

			}
			else{
				printUsage(name);
				return -1;
			}
		}
		else if(foldEnt->d_type == 4){
			if(strcmp(foldEnt->d_name, ".") && strcmp(foldEnt->d_name, "..")){
				string newSrcDir = srcDir;
				newSrcDir.append("/");
				newSrcDir.append(foldEnt->d_name);

				string newDestDir = destDir;
				newDestDir.append("/");
				newDestDir.append(foldEnt->d_name);
				newDestDir.append(".comp");

				DIR *dir = opendir(newSrcDir.c_str());
				compress(dir, newSrcDir, newDestDir, alg, name);
				closedir(dir);
			}
		}
	}
	return 1;
}

int decompress(DIR *dir, string srcDir, string destDir){

#ifdef __unix__
	mkdir(destDir.c_str(), 0777);
#else
	mkdir(destDir.c_str());
#endif

	struct dirent *foldEnt;

	while((foldEnt = readdir(dir)) != NULL){
		string fileName = srcDir;
		fileName.append("/");
		fileName.append(foldEnt->d_name);

		string fileName2 = destDir;
		fileName2.append("/");

		if(foldEnt->d_type == 8){
			for(unsigned int i = strlen(foldEnt->d_name); i > 0; i--){

				if(foldEnt->d_name[i] == '.'){
					if(i == strlen(foldEnt->d_name)-5){
						fileName2.append(foldEnt->d_name);
						fileName2.at(fileName2.size() - 5) = '\0';
						//cout << fileName << endl << fileName2 << endl;
						if(huffmanDecode(fileName, fileName2)){
							cout << "erro ao abrir o ficheiro pretendido" << endl;
							return -1;
						}
					}
					else if(i == strlen(foldEnt->d_name) - 4){
						if(foldEnt->d_name[i+1] == 'l'){
							fileName2.append(foldEnt->d_name);
							fileName2.at(fileName2.size()-4) = '\0';

							LZWdecode(fileName, fileName2);
							break;
						}
						else if(foldEnt->d_name[i+1] == 'r'){
							rledecompress(fileName.c_str(), fileName2.c_str());
							break;
						}
					}
				}
			}
		}
		else if(foldEnt->d_type == 4){
			if(strcmp(foldEnt->d_name, ".") && strcmp(foldEnt->d_name, "..")){
				string newSrcDir = srcDir;
				newSrcDir.append("/");
				newSrcDir.append(foldEnt->d_name);

				string derp = foldEnt->d_name;

				string newDestDir = destDir;
				newDestDir.append("/");
				newDestDir.append(string(derp.begin(), derp.end()-5));

				DIR *dir = opendir(newSrcDir.c_str());
				decompress(dir, newSrcDir, newDestDir);
				closedir(dir);
			}
		}
	}
	return 0;
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


	if(!strcmp(argv[2], "-rle")){
		cout << "WARNING: The Run-Length-Encoding algorithm implemented is unfinished.\n " <<
				"It has only been proven to work on text files.\n" <<
				"It is not recommended that you use it on important files.\n" <<
				"Press ENTER to proceed or CTRL+C to quit now.\n";
		cin.get();
	}

	if(!strcmp(argv[1], "-c")){
		string destDir = argv[3];
		destDir.append(".comp");
		compress(dir, argv[3], destDir, argv[2], argv[0]);
	}

	else if(!strcmp(argv[1], "-d")){
		string srcDir = argv[2];
		string destDir = string(srcDir.begin(), srcDir.end()-5);
		destDir.append(".decomp");
		decompress(dir, srcDir, destDir);
	}

	else
		printUsage(argv[0]);

	closedir(dir);
	cout << "Opearation Complete.\n";
}

/*int main(){
	//lzw
	//LZWencode("tests/doc.pdf","tests/doc.pdf.lzw");
	//LZWencode("tests/duck.bmp","tests/duck.bmp.lzw");
	//LZWencode("tests/flux.exe","tests/flux.exe.lzw");
	//LZWencode("tests/lusiadas.txt","tests/lusiadas.txt.lzw");
	//LZWencode("tests/musica.mp3","tests/musica.mp3.lzw");
	//LZWencode("tests/musica.wav","tests/musica.wav.lzw");
	//std::cout << "done lzw\n";
	//huffmanEncode("tests/doc.pdf","tests/doc.pdf.huf");
	//huffmanEncode("tests/duck.bmp","tests/duck.bmp.huf");
	//huffmanEncode("tests/flux.exe","tests/flux.exe.huf");
	//huffmanEncode("tests/lusiadas.txt","tests/lusiadas.txt.huf");
	//huffmanEncode("tests/musica.mp3","tests/musica.mp3.huf");
	//huffmanEncode("tests/musica.wav","tests/musica.wav.huf");
	//std::cout << "done huffman\n";

	//rlecompress("tests/lusiadas.txt","tests/lusiadas.txt.rle");
	std::ofstream lzw("rle_time.txt", ofstream::trunc);
	for(int i = 100; i < 4000000; i = i+100000 ){
		std::ofstream file("test.txt", ofstream::binary | ofstream::trunc);

		file << generateRandomString(i, 250);
		file.close();
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		rlecompress("test.txt", "dump.txt");
	    high_resolution_clock::time_point t2 = high_resolution_clock::now();
	    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	    lzw << i << "," << duration << endl;
	    cout << "done for " << i << endl;
	}


}*/


