#pragma once
#include <string>

class BookingForm;

class ValidRentDays
{
public:
	static bool validate(int rentDays, const BookingForm* form);
	static std::string error();
};