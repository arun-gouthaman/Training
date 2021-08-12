#pragma once
#include <string>
#include <vector>

class StringFunc
{
private:
	std::vector<std::string> m_StringVals;
	std::vector<int> m_Positions;
public:
	~StringFunc();
	std::vector<std::string> SplitString(const std::string&, const std::string&, bool firstCall = true);
	std::vector<int> FindAllPositions(const std::string&, const std::string&, int startPos = 0);
};