#include <iostream>
#include <fstream>

using namespace std;

int main(){
	streampos size;
	char* memblock;

	ifstream file("LenaRGB.tif", ios::in|ios::binary|ios::ate);

	if(file.is_open())
	{
		cout<<"Ok\n";
		size = file.tellg();
		memblock = new char [size];
		file.seekg(0, ios::beg);
		file.read(memblock, size);
		file.close();
		//for(int i =2;i<;i++)
		cout<<memblock[0]; // little indian
			int i=2;
			cout<<(int)((memblock[i+1]<<8)+memblock[i])<<"\t"; // 42 :)
		delete[] memblock;
	}else{
		cout<<"Not open\n";
	}
	cout<<"Ok\n";

}
