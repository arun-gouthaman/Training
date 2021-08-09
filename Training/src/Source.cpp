#include <iostream>
#include "StringFunc.h"
#include "AttribParser.h"

int main()
{
	std::cout << "TEST" << std::endl;
	std::vector<std::string> stringVec;
	//std::string filePath = "I:/VS_C++/Training/Training/src/userFile.txt";
	//AttribParser attribParser;
	//attribParser.ReadFile(filePath);
	//attribParser.SearchValue("tag1.tag2.tag3~final");
	//attribParser.SearchValue("tag1.tag2~value");
	StringFunc stringFunc;
	stringVec = stringFunc.SplitString("test test test", "");
	for (std::string& splitStr : stringVec)
	{
		std::cout << "string-> " << splitStr << std::endl;
	}

	std::vector<int> stringPos = stringFunc.FindAllPositions("test%^Test%^Test%^", "%^");
	for (int i : stringPos)
	{
		std::cout << i << std::endl;
	}
	return 0;
}