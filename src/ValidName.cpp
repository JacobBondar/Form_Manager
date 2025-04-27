#include "ValidName.h"

//-----------------------------------------------------------------------------

bool ValidName::validate(const std::string& name, const BookingForm* form)
{
	if (name.empty()) return false;

	for (int ch = 0; ch < name.size(); ++ch)
	{
		if (isdigit(name[ch])) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------

std::string ValidName::error()
{
	return "\n	The input should contains only letters!\n";
}