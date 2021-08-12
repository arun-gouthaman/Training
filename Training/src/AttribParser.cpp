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


// WORKS WELL
//std::string AttribParser::SearchValue(const std::string& userIp)
//{
//	std::vector<std::string> tagVal = stringFunc.SplitString(userIp, "~");
//	std::vector<std::string> tags = stringFunc.SplitString(tagVal[0], ".");
//
//	int curTagPos = 0;
//	bool startTagReached = false;
//	bool checkForClose = false;
//	std::string toCloseTag = "";
//	for (std::string line : m_FileData)
//	{
//		if (line._Starts_with("#"))
//		{
//			continue;
//		}
//		if (!startTagReached)
//		{
//			if (checkForClose)
//			{
//				if (line.find(toCloseTag) != std::string::npos)
//				{
//					checkForClose = false;
//				}
//				continue;
//			}
//			if (line.find("<tag") != std::string::npos && line.find(tags[curTagPos]) == std::string::npos)
//			{
//				toCloseTag = line.substr(line.find("<tag") + 1, 5);
//				toCloseTag = "</" + toCloseTag;
//				if (line.find(toCloseTag) == std::string::npos)
//				{
//					checkForClose = true;
//					continue;
//				}
//			}
//
//			if (line.find(tags[curTagPos]) == std::string::npos)
//			{
//				continue;
//			}
//			else
//			{
//				startTagReached = true;
//			}
//		}
//		if (line.find("/tag") != std::string::npos)
//		{
//			return line + " Close Tag found";
//		}
//		if (line.find("/" + tags[curTagPos]) != std::string::npos)
//		{
//			//std::cout << tags[curTagPos] << " Close Tag Reached" << std::endl;
//			return tags[curTagPos] + " Close Tag Reached";
//		}
//		if (line.find(tags[curTagPos]) != std::string::npos)
//		{
//			if (curTagPos == (tags.size() - 1) && line.find(tagVal[1]) != std::string::npos)
//			{
//				//std::cout << line << std::endl;
//				return ExtractValue(line, tagVal[1]);
//			}
//			else if(curTagPos < tags.size() - 1)
//			{
//				++curTagPos;
//				continue;
//			}
//		}
//		if (curTagPos == (tags.size() - 1) && line.find(tagVal[1]) != std::string::npos)
//		{
//			std::cout << line << std::endl;
//			return ExtractValue(line, tagVal[1]);
//		}
//	}
//	//std::cout << "Not found" << std::endl;
//	return "Not found";
//}

//std::string AttribParser::SearchValue(const std::string& userIp)
//{
//	std::vector<std::string> tagVal = stringFunc.SplitString(userIp, "~");
//	std::vector<std::string> tags = stringFunc.SplitString(tagVal[0], ".");
//
//	int curTagPos = 0;
//	bool tagReached = false;
//	for (std::string line : m_FileData)
//	{
//		if (!tagReached && line.find("tag") == std::string::npos)
//		{
//			tagReached = true;
//			continue;
//		}
//		if (line.find("tag") < line.length() && line.find(tags[curTagPos]) > line.length())
//		{
//			return "invalid tag";
//		}
//		else if (curTagPos == tags.size() - 1)
//		{
//			if (line.find(tagVal[1]) < line.length())
//			{
//				std::string valueStr = line.substr(line.find(tagVal[1]));
//				valueStr = valueStr.substr(valueStr.find('"') + 1);
//				valueStr = valueStr.substr(0, valueStr.find('"'));
//				return valueStr;
//			}
//			else
//			{
//				return "value not found in tag";
//			}
//		}
//		if (line.find("/" + tags[curTagPos]) < line.length())
//		{
//			return "tag not found";
//		}
//		if (line.find(tags[curTagPos]) < line.length())
//		{
//			curTagPos += 1;
//			tagReached = true;
//		}
//	}
//}

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
