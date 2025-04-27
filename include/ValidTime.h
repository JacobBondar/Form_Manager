#pragma once
#include <string>
#include "ValidatorNames.h"

class BookingForm;

class ValidTime : public ValidatorNames
{
public:
	static bool validate(const std::string& type, const BookingForm* form);
	static std::string error();

private:
	static int findEnd(std::vector<std::string> names);
};