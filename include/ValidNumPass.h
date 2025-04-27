#pragma once
#include <string>

class BookingForm;

class ValidNumPass
{
public:
	static bool validate(int num, const BookingForm* form);
	static std::string error();
};