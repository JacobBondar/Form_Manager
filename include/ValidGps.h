#pragma once
#include <string>

class BookingForm;

class ValidGps
{
public:
	static bool validate(const std::string& gps, const BookingForm* form);
	static std::string error();
};