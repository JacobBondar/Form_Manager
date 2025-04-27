#pragma once
#include <string>

class BookingForm;

class ValidChildSeat
{
public:
	static bool validate(const std::string& childSit, const BookingForm* form);
	static std::string error();
};