#pragma once
#include <string>
#include <regex>

class BookingForm;

class ValidLaterDate
{
public:
	static bool validate(const std::string& date, BookingForm* form);
	static std::string error();

private:
	static bool compareDates(std::string prevYear, std::string prevMonth,
							 std::string prevDay, std::string thisYear,
							 std::string thisMonth, std::string thisDay);
	static void getDateValues(const std::string& date, std::string& year, 
							  std::string& month, std::string& day);
};