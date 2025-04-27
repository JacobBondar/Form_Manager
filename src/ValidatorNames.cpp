#include "ValidatorNames.h"

//-----------------------------------------------------------------------------

bool ValidatorNames::findValidNames(std::vector<std::string> names, std::stringstream& ss,
							   int start, int end)
{
	std::string token;

	while (std::getline(ss, token, '|'))
	{
		bool found = false;
		for (int cell = start; cell < end; cell++)
		{
			if (token == names[cell]) found = true;
		}
		if (!found) return false;
	}
	return true;
}
