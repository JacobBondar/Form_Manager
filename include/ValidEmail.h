#pragma once

#include <string>
#include <regex>

class BookingForm;

class ValidEmail
{
public:
	static bool validate(const std::string& email, const BookingForm* form);
	static std::string error();
};