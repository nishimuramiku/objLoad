#pragma once

#include<fstream>
#include<vector>
#include <iostream>
#include <string>




class TextLoader
{

public:
	TextLoader();
	~TextLoader();

	bool OpenFile(const char* fileName);
	void SeekContainer(int start, int add);
	int Find(const char* src, int* lineSize); //•¶š‚ÌêŠ•Ô‚·AlineSize‚à“n‚¹‚é



	int GetInt(int* count);
	float GetFloat(int* count);
	std::string  GetString(int* count);



private:
	int GetSize() const;
	int MakeStr(std::string& str);


private:

	int pos;
	int size;

	FILE* file;
	char* container;

	char sep[3] = { '\n', '/',' ' };

};
