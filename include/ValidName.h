#pragma once

#include <string>
#include <iostream>
#include <regex>

class BookingForm;

class ValidName
{
public:
	static bool validate(const std::string& name, const BookingForm* form);
	static std::string error();
};