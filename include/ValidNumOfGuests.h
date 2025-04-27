#pragma once
#include <string>

const int SINGLE_ROOM = 1;
const int DOUBLE_ROOM = 2;
const int PRESIDENTIAL_SUITE_ROOM = 4;
const int MAX_PRESIDENTIAL_SUITE = 7;

class BookingForm;

class ValidNumOfGuests
{
public:
	static bool validate(int num, const BookingForm* form);
	static std::string error();

private:
	static bool checkCases(int numOfGuests, int switchCaseValue);
};