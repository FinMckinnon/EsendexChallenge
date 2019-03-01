#pragma once
#include <vector>
#include <sstream>

// Processes involving string manipulation
struct stringManipulation
{
	//Splits a string into a vector using a comma-delimiter
	std::vector<std::string> splitString(std::string line)
	{
		std::vector<std::string> result;
		std::stringstream ss(line);
		while (ss.good())
		{
			std::string substr;
			getline(ss, substr, ',');
			result.push_back(substr);
		}
		return result;
	}

	//Concatenate a vector of char into a string
	std::string concatChar(std::vector<char> charVector)
	{
		std::string str;

		for (char& c : charVector)
		{
			str += c;
		}
		return str;
	}

	std::string ToUpper(std::string input)
	{
		std::string upperCaseString;

		for(int c = 0; c < input.length(); c++)
		{
			upperCaseString += (toupper(input[c]));
		}

		return upperCaseString;
	}
};

