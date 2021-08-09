#pragma once
#include <vector>
#include <string>

#include "StringFunc.h"

class AttribParser
{
public:
	AttribParser();
	~AttribParser();
	void ReadFile(const std::string&);
	std::string SearchValue(const std::string&);
private:
	std::vector<std::string> m_FileData;
	std::pair<std::vector<std::string>, std::string> SplitInput(const std::string&);
	std::vector<std::string> SplitTag(const std::string&, const char&);
	void PrintVecValues(std::vector<std::string>&);
	StringFunc stringFunc;
	
};