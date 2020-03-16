#include "TextLoader.h"
#include<string.h>


TextLoader::TextLoader()
	:file(nullptr)
	, container(nullptr)
	, pos(0)
	, size(0)
{
}

TextLoader::~TextLoader()
{
	if (container != nullptr)
	{
		delete container;
		container = nullptr;

	}

}


bool TextLoader::OpenFile(const char* fileName)
{
	errno_t error = fopen_s(&file, fileName, "r");

	if (error != 0)
	{
		fclose(file);
		return false;
	}

	size = GetSize();
	container = new char[size + 1];

	fread(container, sizeof(char), size / sizeof(char), file);
	container[size] = '\0';
	//printf("%s", container);

	fclose(file);
	return true;

}

int TextLoader::GetSize() const
{
	if (fseek(file, 0L, SEEK_END) == 0)
	{
		fpos_t pos;
		if (fgetpos(file, &pos) == 0)
		{
			fseek(file, 0L, SEEK_SET);
			return pos;
		}
	}
}

void TextLoader::SeekContainer(int start, int add)
{
	pos += start + add;
}

int  TextLoader::Find(const char* src, int* lineSize)
{
	char* temp = strstr(container + pos, src);
	if (temp == nullptr)
	{
		return -1;
	}
	else
	{
		char* temp_e = strstr(temp, "\n");


		int start = strlen(container + pos) - strlen(temp);


		if (temp_e != nullptr)
		{
			*lineSize = strlen(temp) - strlen(temp_e);
		}

		return start;
	}
}


std::string TextLoader::GetString(int* count)
{
	std::string str = "";

	*count = MakeStr(str);

	return str;

}

float TextLoader::GetFloat(int* count)
{
	std::string str = "";

	*count = MakeStr(str);

	return  atof(str.c_str());

}

int TextLoader::GetInt(int* count)
{

	std::string str = "";

	*count = MakeStr(str);

	return  atoi(str.c_str());

}

int TextLoader::MakeStr(std::string& str)
{
	int i;
	bool flag = true;


	for (i = 0;; i++)
	{
		for (char c : sep)
		{
			if (container[i + pos] == c)
			{
				flag = false;
				break;
			}
		}
		str.push_back(container[i + pos]);
		if (!flag)
		{
			break;
		}
	}
	str += '\0';
	pos += i + 1;

	return i + 1;

}