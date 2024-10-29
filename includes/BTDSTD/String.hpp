#pragma once

//defines string operations

#include <string>
#include <vector>

namespace BTD::String
{
	//splits a string by a delimiter
	static std::vector<std::string> SplitStrIntoArrayByDelimiter(const char* str, const char d)
	{
		std::vector<std::string> strs; strs.reserve(5);

		std::string data = "";
		for (size_t i = 0; i < strlen(str); ++i)
		{
			if (str[i] == d)
			{
				strs.emplace_back(data);
				data = "";
				continue;
			}

			data += str[i];
		}
		strs.emplace_back(data);

		return strs;
	}
}