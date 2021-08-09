#include <iostream>
#include "StringFunc.h"
#include "AttribParser.h"

void SearchVal()
{
	AttribParser attribParser;
	std::string filePath = "I:/VS_C++/Training/Training/src/userFile.txt";
	attribParser.ReadFile(filePath);
	std::cout << attribParser.SearchValue("tag1.tag2.tag3~final") << std::endl;
	std::cout << attribParser.SearchValue("tag1.tag2.tag3~another") << std::endl;
	std::cout << attribParser.SearchValue("tag1.tag2~name") << std::endl;
	std::cout << attribParser.SearchValue("tag1~value") << std::endl;
}

void SpliStringTest()
{
	StringFunc stringFunc;
	std::vector<std::string>stringVec = stringFunc.SplitString("test test test", " ");
	for (std::string& splitStr : stringVec)
	{
		std::cout << "string-> " << splitStr << std::endl;
	}
}

void FindAllPositionsTest()
{
	StringFunc stringFunc;
	std::vector<int> stringPos = stringFunc.FindAllPositions("test%^Test%^Test%^", "%^");
	for (int i : stringPos)
	{
		std::cout << i << std::endl;
	}
}

int main()
{
	//SearchVal();
	//SpliStringTest();
	//FindAllPositionsTest();

	return 0;
}