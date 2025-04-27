#include "ValidLocation.h"

//-----------------------------------------------------------------------------

bool ValidLocation::validate(const std::string& address, const BookingForm* form)
{
	std::regex addressRegex(R"(^[a-zA-Z\s]+-[0-9]+-[a-zA-Z\s]+$)");
	return std::regex_match(address, addressRegex);
}

//-----------------------------------------------------------------------------

std::string ValidLocation::error()
{
	return "\n	The Location input is invalid!\n";
}