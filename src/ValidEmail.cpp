#include "ValidEmail.h"

//-----------------------------------------------------------------------------

bool ValidEmail::validate(const std::string& email, const BookingForm* form)
{
	std::regex emailRegex(R"(^[A-Za-z0-9._-]+@[A-Za-z0-9._-]+(\.[A-Za-z]{2,})+$)");
	return std::regex_match(email, emailRegex);
}

//-----------------------------------------------------------------------------

std::string ValidEmail::error()
{
	return "\n	The Email input is invalid!\n";
}