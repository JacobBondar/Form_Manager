#pragma once
#include <string>

class BookingForm;

class ValidType
{
public:
	static bool validate(const std::string& type, const BookingForm* form);
	static std::string error();
};