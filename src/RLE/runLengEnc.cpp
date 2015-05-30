#include "RLE.h"
using namespace std;


float compress(const char *fname, const char *cname)
{
    fstream file;
    fstream compressed;
    char character;
    char next_character;
    streampos fsize = 0;
    int frequency = 1;
    int write_pos = 0;

    file.open(fname, ios::in | ios::ate | ios::binary);
    compressed.open(cname, ios::out | ios::trunc | ios::binary);
    fsize = file.tellg();

    for(int i = 0; i < fsize; i++)
    {
        file.seekg(i, ios::beg);
        file.read((char*)&character, sizeof(char));
        next_character = file.peek();
        if(next_character != character)
        {
        	if (frequency > 2)
        	{
        		ostringstream ss;
        		ss << frequency-2;
        		string freq_str = ss.str();
        		for (size_t i = 0; i < freq_str.length(); i++)
        			freq_str[i] -= '0' - 22;
        		compressed.seekp(write_pos, ios::beg);
        		compressed.write(&freq_str[0], freq_str.length()*sizeof(char));
        		write_pos += freq_str.length();
        		frequency = 1;
        	}
        	while (frequency > 0)
        	{
        		compressed.seekp(write_pos, ios::beg);
        		compressed.write((char*)&character, sizeof(char));
        		write_pos++;
        		frequency--;
        	}
        }
        frequency++;
    }
    file.close();
    compressed.close();

    return (write_pos / float(fsize));
}

void decompress(const char *fname, const char *uname)
{
    fstream file;
    fstream ufile;
    char character;
    int frequency = 0;
    streampos fsize = 0;
    int write_pos = 0;

    file.open(fname, ios::ate | ios::in | ios::binary);
    ufile.open(uname, ios::trunc | ios::out | ios::binary);
    fsize = file.tellg();

    for(int i = 0; i < fsize; i++)
    {
        file.seekg(i, ios::beg);
        file.read((char*)&character, sizeof(char));
        frequency = 0;
        while (character >= 22 && character <= 31)
        {
        	frequency *= 10;
        	frequency += character - 22;
        	file.seekg(++i, ios::beg);
        	file.read((char*)&character, sizeof(char));
        }
        if (frequency != 0) frequency++;
        for(int j = 0; j <= frequency; j++)
        {
            ufile.seekp(write_pos, ios::beg);
            ufile.write((char*)&character, sizeof(char));
            write_pos++;
        }
    }
    file.close();
    ufile.close();
}
