#pragma once
#include <vector>
#include <string>

class AttribParser
{
public:
	AttribParser();
	~AttribParser();
	void ReadFile(const std::string&);
	void SearchValue(const std::string&);
private:
	std::vector<std::string> m_FileData;
	std::pair<std::vector<std::string>, std::string> SplitInput(const std::string&);
	std::vector<std::string> SplitTag(const std::string&, const char&);
	
};