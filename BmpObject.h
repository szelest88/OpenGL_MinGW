#include <iostream>
#include <fstream>

using namespace std;

class BmpObject{
private:
	BmpObject(); // eeekhm... has to be? :F
	public:
		unsigned char* data;
		int width, height;
		BmpObject(string filename);
};
