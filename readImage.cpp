#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include "filetypes.h"
#include <array>
using namespace std;

int main(){

	ifstream ifp("FAT16Partition.001", ifstream::in|ifstream::binary);
	char c = 0;
	File<ZIP> png;

	vector<char> buffer;
	bool foundPNG = false;
	int count = 1;
	while(!ifp.eof()){

		ifp.read(&c, 1);
		buffer.push_back(c);

		if(buffer.size() >= 8 && !foundPNG){

			if(png.equalHeader(buffer)){
				foundPNG = true;
			}else{
				buffer.erase(buffer.begin());
			}

		}else if(buffer.size() >= 8 && foundPNG){

			if(png.equalTrailer(buffer)){

				if(png.getExt() == ".zip"){
					//read in more bytes until 00000000
					for(int i = 0; i < 18; i++){
						ifp.read(&c, 1);
						buffer.push_back(c);
					}
				}
				png.createFile(buffer, count++);
				buffer.clear();
				foundPNG = false;
			}
		}

	}
	return 0;
}