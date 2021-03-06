#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <iterator>
using namespace std;

template <typename T>
class File{

	public:

		File(){
			t = new T();
		}

		bool equalHeader(vector<char> buffer){
			return mismatch(t->header.begin(), t->header.end(), buffer.begin()).first == t->header.end();
		}

		bool equalTrailer(vector<char> buffer){
			auto itr = buffer.begin();
			advance(itr, buffer.size()-8);
			return mismatch(t->trailer.begin(), t->trailer.end(), itr).first == t->trailer.end();
		}

		void createFile(vector<char> buffer, int fileNumber){

			stringstream oss;
			oss << fileNumber << t->ext;
			string file = oss.str();

			ofstream ofp(file, ofstream::out|ofstream::binary);

			copy(buffer.begin(), buffer.end(), ostream_iterator<char>(ofp));

			ofp.close();
		}

		string getExt(){
			return t->ext;
		}
	private:
		T *t;
};

struct PNG{
	string ext = ".png";
	array<char, 8> header{{0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A}};
	array<char, 8> trailer{{0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82}};
};

struct ZIP{
	string ext = ".zip";
	array<char, 4> header{{0x50, 0x4B, 0x03, 0x04}};
	array<char, 4> trailer{{0x50, 0x4B, 0x05, 0x06}};
};

struct GIF{
	string ext = ".gif";
	array<char, 6> header{{0x47, 0x49, 0x46, 0x38, 0x39, 0x61}};
	array<char, 2> trailer{{0x00, 0x3B}};
};

struct RTF{
	string ext = ".rtf";
	array<char, 6> header{{0x7B, 0x5C, 0x72, 0x74, 0x66, 0x31}};
	array<char, 7> trailer{{0x5C, 0x70, 0x61, 0x72, 0x20, 0x7D, 0x7D}};
}