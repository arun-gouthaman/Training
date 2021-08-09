#include <iostream>
#include <fstream>

#include "AttribParser.h"

AttribParser::AttribParser()
{
}

AttribParser::~AttribParser()
{
	m_FileData.clear();
}

void AttribParser::ReadFile(const std::string& filePath)
{
	m_FileData.clear();
	std::ifstream userFile(filePath);
	std::string line;
	while (std::getline(userFile, line))
	{
		m_FileData.push_back(line);
	}
	userFile.close();
}

void AttribParser::PrintVecValues(std::vector<std::string>& ipVec)
{
	for (std::string line : ipVec)
	{
		std::cout << line << std::endl;
	}
}

std::string AttribParser::SearchValue(const std::string& userIp)
{
	std::vector<std::string> tagVal = stringFunc.SplitString(userIp, "~");
	std::vector<std::string> tags = stringFunc.SplitString(tagVal[0], ".");

	int curTagPos = 0;
	bool tagReached = false;
	for (std::string line : m_FileData)
	{
		if (!tagReached && line.find("tag") == std::string::npos)
		{
			tagReached = true;
			continue;
		}
		if (line.find("tag") < line.length() && line.find(tags[curTagPos]) > line.length())
		{
			return "invalid tag";
		}
		else if (curTagPos == tags.size() - 1)
		{
			if (line.find(tagVal[1]) < line.length())
			{
				std::string valueStr = line.substr(line.find(tagVal[1]));
				valueStr = valueStr.substr(valueStr.find('"') + 1);
				valueStr = valueStr.substr(0, valueStr.find('"'));
				return valueStr;
			}
			else
			{
				return "value not found in tag";
			}
		}
		if (line.find("/" + tags[curTagPos]) < line.length())
		{
			return "tag not found";
		}
		if (line.find(tags[curTagPos]) < line.length())
		{
			curTagPos += 1;
			tagReached = true;
		}
	}
}

std::pair<std::vector<std::string>, std::string> AttribParser::SplitInput(const std::string& userIp)
{
	std::vector<std::string> tags;
	std::pair<std::vector<std::string>, std::string> tagVal(tags, "");
	bool delimiterChar = false;
	int charPos = userIp.find("~");
	if (charPos < userIp.length())
	{
		std::string tag = userIp.substr(0, charPos);
		if (tag.find(".") < tag.length())
		{
			tagVal.first = SplitTag(tag, '.');
		}
		else
		{
			tagVal.first.push_back(tag);
		}
		tagVal.second = userIp.substr(charPos+1, userIp.length());
	}
	else
	{
		std::cout << "split character not found" << std::endl;
	}
	return tagVal;
}

std::vector<std::string> AttribParser::SplitTag(const std::string& tag, const char& seperator)
{
	std::vector<std::string> tags;
	std::string tagVal = "";
	for (int i = 0; i < tag.length(); i++)
	{
		if (tag[i] != seperator)
		{
			tagVal += tag[i];
		}
		else
		{
			tags.push_back(tagVal);
			tagVal = "";
		}
	}
	if (tagVal.length())
	{
		tags.push_back(tagVal);
	}
	return tags;
}
