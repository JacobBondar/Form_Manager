#pragma once
#include <string>
#include <regex>
#include "ValidatorNames.h"

class BookingForm;

class ValidButtonInput : public ValidatorNames
{
public:
	static bool validate(const std::string& type, const BookingForm* form);
	static std::string error();
};