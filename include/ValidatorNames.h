#pragma once
#include <string>
#include <vector>
#include <sstream>

class ValidatorNames
{
public:
	ValidatorNames() = default;
	~ValidatorNames() = default;

protected:
	static bool findValidNames(std::vector<std::string> names, std::stringstream& ss,
						int start, int end);
};