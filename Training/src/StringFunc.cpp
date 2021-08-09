#include "StringFunc.h"
#include<iostream>

StringFunc::~StringFunc()
{
	m_StringVals.clear();
}

std::vector<std::string> StringFunc::SplitString(const std::string& ipString, const std::string& ipDelimiter)
{
	if (ipString.length() < 1)
	{
		return m_StringVals;
	}
	if (ipDelimiter.length() < 1)
	{
		m_StringVals.push_back(ipString);
		return m_StringVals;
	}
	if (ipString.find(ipDelimiter) != std::string::npos)
	{
		int pos = ipString.find(ipDelimiter);
		std::string splitStr = ipString.substr(0, pos);
		m_StringVals.push_back(splitStr);
		if (ipString.substr(pos + ipDelimiter.length(), ipString.length()).length()+1 > 0)
		{
			SplitString(ipString.substr(pos + ipDelimiter.length(), ipString.length()), ipDelimiter);
		}
	}
	else
	{
		m_StringVals.push_back(ipString);
	}
	return m_StringVals;
}

std::vector<int> StringFunc::FindAllPositions(const std::string& ipString, const std::string& findString, int startPos, int posTotal)
{
	int pos;
	if (ipString.find(findString) == std::string::npos)
	{
		return m_Positions;
	}
	else
	{
		pos = ipString.find(findString, startPos);
		m_Positions.push_back(pos);
		startPos = pos + findString.length();
		if (startPos < ipString.length())
		{
			FindAllPositions(ipString, findString, startPos);
		}
	}
	return m_Positions;
}
