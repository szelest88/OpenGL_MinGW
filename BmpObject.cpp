#include "BmpObject.h"

#include <iostream>
#include <fstream>

using namespace std;

BmpObject::BmpObject(string fileName) {
 	cout<<"Opening file: " << fileName <<"\n";

 	std::ifstream file(fileName.c_str(), ios::binary);

	if(file)
	{
		char* signature = new char[3];
		int filesize = 0, dataOffset = 0;
		int infoHeaderSize = 0, width = 0, height = 0;
		short bitcount = 0;
		unsigned char data1;
        file.seekg(0,std::ios::beg);
		file.read((char*)signature,2);
		file.read((char*)&filesize, sizeof(filesize));
		file.seekg(10);//14
		file.read((char*)&dataOffset, sizeof(filesize));
		file.seekg(14);
		file.read((char*)&infoHeaderSize, 4);
		file.read((char*)&width, 4);
		file.read((char*)&height, 4);
		file.seekg(28);
		file.read((char*)&bitcount, 2);
		
		file.seekg(dataOffset);
		file.read((char*)&data1,1);
		signature[2]=0;
		cout<<"Signature: "<<signature<<"\n";
		cout<<"Filesize: "<<filesize<<"\n";
		cout<<"InfoHeaderSize: "<<infoHeaderSize<<"\n";

		cout<<"dataOffset: "<<dataOffset<<"\n";

		cout<<"width: "<<width<<"\n";
		cout<<"height: "<<height<<"\n";
		cout<<"bitcount: "<<bitcount<<"\n";
		cout<<"data1:"<<(int)data1<<"\n";
	}else{
		cout<<"Not open\n";
	}
 }
