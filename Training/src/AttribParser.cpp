#include <iostream>
#include <fstream>

#include "AttribParser.h"

AttribParser::AttribParser()
{
}

AttribParser::~AttribParser()
{
}

void AttribParser::ReadFile(const std::string& filePath)
{
	std::ifstream userFile(filePath);
	std::string line;
	while (std::getline(userFile, line))
	{
		m_FileData.push_back(line);
	}
	userFile.close();
}

void AttribParser::SearchValue(const std::string& tag)
{
	std::pair<std::vector<std::string>, std::string> inputValues;
	inputValues = SplitInput(tag);
	int lineCount = 0;
	bool tagReached = false;
	int curTagPos = 0;
	std::string curTag = inputValues.first[curTagPos];
	std::string prevTag = inputValues.first[curTagPos];

	for (std::string line : m_FileData)
	{
		if (line.find("tag") < line.length() && line.find(curTag) > line.length())
		{
			std::cout << "invalid tag" <<std::endl;
			return;
		}
		if (curTagPos == inputValues.first.size() - 1)
		{
			if (line.find(inputValues.second) < line.length())
			{
				std::string valueStr = line.substr(line.find(inputValues.second));
				valueStr = valueStr.substr(valueStr.find('"')+1);
				valueStr = valueStr.substr(0, valueStr.find('"'));
				std::cout << valueStr << std::endl;
				return;
			}
		}
		if (line.find(curTag) < line.length())
		{
			curTagPos += 1;
			prevTag = curTag;
			curTag = inputValues.first[curTagPos];
		}
		if (line.find("/" + prevTag) < line.length() || line.find("/" + curTag) < line.length())
		{
			std::cout << "tag not found" << std::endl;
			return;
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
