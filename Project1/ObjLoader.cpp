#include "ObjLoader.h"
#include"TextLoader.h"


ObjLoader::ObjLoader()
	:lineSize(0)
{
	textLoader = new TextLoader;
	Init();

}


ObjLoader::~ObjLoader()
{
	if (textLoader != nullptr)
	{
		delete textLoader;
		textLoader = nullptr;
	}
}



void ObjLoader::LoadObj(Data* data)
{
	//std::cout << "mtllib" ;
	while (true)
	{
		int result = textLoader->Find("mtllib ", &lineSize);
		if (result == -1)
		{
			break;
		}

		int tag = strlen("mtllib ");
		textLoader->SeekContainer(result, tag);

		while (true)
		{
			std::string str = textLoader->GetString(&count);
			sum += count;
			std::cout << " " << str;
			if (sum > lineSize - tag)
			{
				flag = false;
				break;
			}

		}
		if (!flag)
		{
			textLoader->SeekContainer(0, lineSize - tag - sum + 1);
		}


	}

	/*while (true)
	{*/
		int result = textLoader->Find("g ", &lineSize);
		/*if (result == -1)
		{
			break;
		}*/
		int tag = strlen("g ");
		textLoader->SeekContainer(result, tag);

		Init();

		while (true)
		{
			std::string  s = textLoader->GetString(&count);
			sum += count;
			
			if (sum > lineSize - tag)
			{
				flag = false;
				break;
			}
		}
		if (!flag)
		{
			textLoader->SeekContainer(0, lineSize - tag - sum + 1);
		}


	//}



	//std::cout << "v" ;
	while (true)
	{

		int result = textLoader->Find("v ", &lineSize);

		if (result == -1)
		{
			break;
		}

		int tag = strlen("v ");
		textLoader->SeekContainer(result, tag);
		//textLoader->SeekContainer(0, tag);



		Init();
		std::vector<float> temp;

		while (true)
		{

			float f = textLoader->GetFloat(&count);
			sum += count;
			//std::cout << " " << f ;
			temp.push_back(f);
			if (sum > lineSize - tag)
			{
				flag = false;
				break;
			}

		}
		data->v.push_back(temp);
		if (!flag)
		{
			std::cout << std::endl;
			textLoader->SeekContainer(result, lineSize - tag - sum + 1);
		}

	}



	//std::cout << "vt" ;
	while (true)
	{
		int result = textLoader->Find("vt ", &lineSize);
		if (result == -1)
		{
			break;
		}
		int tag = strlen("vt ");
		textLoader->SeekContainer(result, tag);

		Init();
		std::vector<float> temp;

		while (true)
		{
			float f = textLoader->GetFloat(&count);
			sum += count;
			//std::cout << " " << f ;
			temp.push_back(f);
			if (sum > lineSize - tag)
			{
				flag = false;
				break;
			}
		}
		data->vt.push_back(temp);
		if (!flag)
		{

			std::cout << std::endl;
			textLoader->SeekContainer(0, lineSize - tag - sum + 1);
		}


	}



	//std::cout << "usemtl";
	while (true)
	{

		int result = textLoader->Find("usemtl ", &lineSize);
		if (result == -1)
		{
			break;
		}
		int tag = strlen("usemtl ");
		textLoader->SeekContainer(result, tag);
		Init();
		std::string temp;

		while (true)
		{
			std::string  str = textLoader->GetString(&count);
			sum += count;
			//std::cout << " " << str;
			temp = str;
			if (sum > lineSize - tag)
			{
				flag = false;
				break;
			}
		}
		if (!flag)
		{
			textLoader->SeekContainer(0, lineSize - tag - sum + 1);

		}
		data->mtl.push_back(temp);
	}


	//std::cout << "s";
	while (true)
	{

		int result = textLoader->Find("s ", &lineSize);

		if (result == -1)
		{
			break;
		}

		int tag = strlen("s ");
		textLoader->SeekContainer(result, tag);

		Init();


		while (true)
		{
			std::string str = textLoader->GetString(&count);
			sum += count;
			std::cout << " " << str;
			if (count >= lineSize - tag)
			{
				flag = false;
				break;
			}
		}
		flag = false;
		if (!flag)
		{
			textLoader->SeekContainer(0, lineSize - tag - sum + 1);
		}
	}



	//std::cout << "f ";
	while (true)
	{

		int result = textLoader->Find("f ", &lineSize);
		if (result == -1)
		{
			break;
		}

		int tag = strlen("f ");
		textLoader->SeekContainer(result, tag);

		Init();

		while (true)
		{
			int i = textLoader->GetInt(&count);
			sum += count;
			//std::cout  << i << "/" ;
			data->f.push_back(i);
			if (sum > lineSize - tag)
			{
				flag = false;
				break;
			}
		}
		if (!flag)
		{
			std::cout << std::endl;
			textLoader->SeekContainer(0, lineSize - tag - sum + 1);

		}
	}
}

bool ObjLoader::OpenFile(const char* fileName)
{
	bool result = textLoader->OpenFile(fileName);
	if (!result)
	{
		return false;
	}
	else return true;
}


void ObjLoader::Init()
{
	flag = true;
	sum = 0;
	count = 0;
}