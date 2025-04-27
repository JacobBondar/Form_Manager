#pragma once
#include <string>
#include <vector>
#include "ValidatorNames.h"

class BookingForm;

class ValidRequest : public ValidatorNames
{
public:
	static bool validate(const std::string& type, const BookingForm* form);
	static std::string error();

private:
	static bool checkSpecialEvent(const std::string& type, const BookingForm* form);
	static bool validNumPass(const std::string& type, const BookingForm* form);
	static int findStart(std::vector<std::string> names);
	static void setStringValidate(std::string og, std::string& first, std::string& second);
};