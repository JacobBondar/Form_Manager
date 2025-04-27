#include "ValidTime.h"
#include "BookingForm.h"

//-----------------------------------------------------------------------------

bool ValidTime::validate(const std::string& type, const BookingForm* form)
{
	std::vector<std::string> names = form->getNames();

	std::stringstream ss(type);
	int end = findEnd(names);

	return findValidNames(names, ss, 0, names.size());
}

//-----------------------------------------------------------------------------

int ValidTime::findEnd(std::vector<std::string> names)
{
	auto it = std::find(names.begin(), names.end(), "\0");

	return std::distance(names.begin(), it);
}

//-----------------------------------------------------------------------------

std::string ValidTime::error()
{
	return "\n	The Preferred Time input is invalid!\n";
}