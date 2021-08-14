#include <iostream>
#include <algorithm>
#include "StringFunc.h"
#include "AttribParser.h"

void SearchVal()
{
	AttribParser attribParser;
	std::string filePath = "I:/VS_C++/Training/Training/src/userFile.txt";
	attribParser.ReadFile(filePath);
	std::cout << attribParser.SearchValue("tag6.tag8~val") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("tag1.tag2.tag3~another") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("tag1.tag2~name") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("tag1~value") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("tag2~name") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("tag3~another") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("tag3~final") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("tag1.tag2~name") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("tag1.tag3~final") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("tag2.tag3~final") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("tag5.tag7~new_val") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("tag6.tag8~intval") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("a.b.c~final") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("a.b.c~another") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("a.b~name") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("a~value") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("b~name") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("c~another") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("c~final") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("a.c~final") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("b.c~final") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("tag4~v1") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("tag4~v2") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("a~value") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("b~value") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("a.b~size") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("a.b~value") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("a.b.c~height") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("a.c~height") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("a.d.e~strength") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("a.c.d.e~strength") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("d~sze") << std::endl << std::endl;
	//std::cout << attribParser.SearchValue("a.c.d~size") << std::endl << std::endl;
}

void SpliStringTest()
{
	StringFunc stringFunc;
	std::vector<std::string>stringVec = stringFunc.SplitString("test%test%test", "%");
	for (std::string& splitStr : stringVec)
	{
		std::cout << "string-> " << splitStr << std::endl;
	}
	stringVec = stringFunc.SplitString("string split test", " ");
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
}