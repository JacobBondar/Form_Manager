#pragma once
#include <string>
#include <regex>

class BookingForm;

class ValidDate
{
public:
	static bool validate(const std::string& date, BookingForm* form);
	static std::string error();
};