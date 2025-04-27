#pragma once

#include <string>
#include <regex>

class BookingForm;

class ValidLocation
{
public:
	static bool validate(const std::string& address, const BookingForm* form);
	static std::string error();
};