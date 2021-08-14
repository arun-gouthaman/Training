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

const std::string AttribParser::ExtractValue(const std::string& line, const std::string& value)
{
	std::string valueStr = line.substr(line.find(value));
	valueStr = valueStr.substr(valueStr.find('"') + 1);
	valueStr = valueStr.substr(0, valueStr.find('"'));
	return valueStr;
}

std::string AttribParser::SearchValue(const std::string& userIp)
{
	//std::cout << userIp << std::endl;
	std::vector<std::string> tagVal = stringFunc.SplitString(userIp, "~");
	std::vector<std::string> tags = stringFunc.SplitString(tagVal[0], ".");
	std::string value = tagVal[1];
	int curTagpos = 0;
	int tagsSize = tags.size();

	bool startTagReached = false;
	bool endTagReached = false;
	std::string toBeClosed = "";
	std::string curTag = tags[curTagpos];
	bool multiLineComment = false;
	for (std::string line : m_FileData)
	{
		if (line[0] == '#')
		{
			continue;
		}
		if (!toBeClosed.empty())
		{
			if (findStr(line, "</" + toBeClosed))
			{
				toBeClosed.clear();
			}
			continue;
		}
		if (line[0] == '<' && line[1] != '/' && !findStr(line, "<" + curTag))
		{
			//std::cout << "To be closed " << line.substr(1, line.find(" ")) << std::endl;
			if (findStr(line, " "))
			{
				toBeClosed = line.substr(1, line.find(" ") - 1);
			}
			else if (findStr(line, ">"))
			{
				toBeClosed = line.substr(1, line.find(">") - 1);
			}
			if (findStr(line, "</" + toBeClosed))
			{
				toBeClosed.clear();
			}
			continue;
		}
		if (!startTagReached)
		{
			if(findStr(line, "<" + curTag))
			{
				startTagReached = true;
			}
			else
			{
				continue;
			}
		}
		if (findStr(line, "</" + curTag) ||
			(curTagpos>0 && findStr(line, "</" + tags[curTagpos-1])))
		{
			return "Not Found!";
		}
		if (curTagpos == tagsSize - 1)
		{
			if (findStr(line, "<" + curTag + " "))
			{
				if (findStr(line, value))
				{
					return ExtractValue(line, value);
				}
			}
		}
		else
		{
			curTagpos++;
			curTag = tags[curTagpos];
		}
	}
	return "Not Found!";
}

/*
* Working Block
std::string AttribParser::SearchValue(const std::string& userIp)
{
	std::vector<std::string> tagVal = stringFunc.SplitString(userIp, "~");
	std::vector<std::string> tags = stringFunc.SplitString(tagVal[0], ".");
	std::string value = tagVal[1];

	int curTagpos = 0;
	int tagsSize = tags.size();

	bool startTagReached = false;
	bool endTagReached = false;
	std::string toBeClosed = "";

	for (std::string line : m_FileData)
	{
		if (line.length() == 0)
		{
			continue;
		}
		if (line._Starts_with("#"))
		{
			continue;
		}
		// if tag not opened yet and current line has no open tag move to next line
		if (!startTagReached && toBeClosed.length() == 0)
		{
			if (line.find("<"+tags[curTagpos]) != std::string::npos)
			{
				startTagReached = true;
			}
			else if (line.find("<tag") != std::string::npos)
			{
				toBeClosed = line.substr(1, 4);
			}
			else
			{
				continue;
			}
		}
		if (toBeClosed.length() > 0)
		{
			if (line.find("</" + toBeClosed) != std::string::npos)
			{
				toBeClosed = "";
			}
			continue;
		}
		else
		{
			if (startTagReached && line.find("</tag") != std::string::npos)
			{
				return line + " End Tag Reached, Unable to find pattern, Terminating";
			}
		}
		if (line.find("<tag") != std::string::npos && line.find("<"+tags[curTagpos]) == std::string::npos)
		{
			toBeClosed = line.substr(1, 4);
			if (line.find("</" + toBeClosed) != std::string::npos)
			{
				toBeClosed = "";
			}
			continue;
		}
		if (line.find("</" + tags[curTagpos]) != std::string::npos)
		{
			std::cout << tags[curTagpos] << "closed";
			return "";
		}
		if (curTagpos == tagsSize - 1)
		{
			if (!endTagReached)
			{
				if (line.find(tags[curTagpos]) == std::string::npos)
				{
					continue;
				}
				else
				{
					endTagReached = true;
				}
			}
			if (line.find(value) != std::string::npos)
			{
				return ExtractValue(line, value);
			}
			else
			{
				continue;
			}
		}
		else
		{
			++curTagpos;
		}
	}
	return "End of file reached, unable to find pattern";
}
*/