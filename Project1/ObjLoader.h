#pragma once

#include<vector>

class TextLoader;


struct Data
{
	std::vector<std::vector<float>> v;
	std::vector<std::vector<float>> vt;
	std::vector <std::string> mtl;
	std::vector<int> f;

};


class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	void LoadObj(Data* data);
	bool OpenFile(const char* fileName);
	void Init();

private:

private:
	TextLoader* textLoader;

	int lineSize;
	bool flag;
	int sum;
	int count;

};