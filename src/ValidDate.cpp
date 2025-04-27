#include "ValidDate.h"

//-----------------------------------------------------------------------------

bool ValidDate::validate(const std::string& date, BookingForm* form)
{
	std::regex dateRegex(R"(^[0-9]{4}(-[0-9]{2}){2})");
	if (!std::regex_match(date, dateRegex)) return false;

	auto year = stoi(date.substr(0, 4));
	auto month = stoi(date.substr(5, 2));
	auto day = stoi(date.substr(8, 2));

	return month > 0 && month < 13 && day > 0 && day < 32 && year > 0;
}

//-----------------------------------------------------------------------------

std::string ValidDate::error()
{
	return "\n	The Date input is invalid!\n";
}