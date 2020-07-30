#pragma once

#include <sstream>

static class Utils
{
public:
	static std::string float_to_str(const float value, const int precision = 3)
	{
		std::ostringstream outStream;
		outStream.precision(precision);

		outStream << std::fixed << value;
		return outStream.str();
	}
};