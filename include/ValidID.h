#pragma once
#include <string>
#include <regex>
class BookingForm;

class ValidID
{
public:
	static bool validate(uint32_t id, const BookingForm* form);
	static std::string error();

private:
	static int calcSumDigit(int id);
	static bool checkSize(uint32_t id);
};