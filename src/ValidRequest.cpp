#include "ValidRequest.h"
#include "BookingForm.h"

//-----------------------------------------------------------------------------

bool ValidRequest::validate(const std::string& type, const BookingForm* form)
{
	if(!checkSpecialEvent(type, form)) return false;
	if (!validNumPass(type, form)) return false;

	std::vector<std::string> names = form->getNames();
	std::stringstream ss(type);

	int indexStart = findStart(names);

	return findValidNames(names, ss, indexStart, names.size());
}

//-----------------------------------------------------------------------------

int ValidRequest::findStart(std::vector<std::string> names)
{
	int cell;
	for (cell = 0; cell < names.size(); ++cell)
	{
		if (names[cell] == "\0") break;
	}
	return cell + 1;
}

//-----------------------------------------------------------------------------

bool ValidRequest::checkSpecialEvent(const std::string& type, const BookingForm* form)
{
	std::string test = form->getTypeName();
	std::string firstString, secondString;
	setStringValidate(test, firstString, secondString);

	if (type.find(firstString) != std::string::npos && 
		type.find(secondString) != std::string::npos)
		return false;

	return true;
}

//-----------------------------------------------------------------------------

bool ValidRequest::validNumPass(const std::string& type, const BookingForm* form)
{
	int numPass = form->getAmount();
	std::string test = form->getValidateName();
	std::string firstString, secondString;
	setStringValidate(test, firstString, secondString);

	if (type.find(firstString) != std::string::npos)
	{
		if (numPass % 4 != 0) return false;
	}

	if (type.find(secondString) != std::string::npos)
	{
		if (numPass > 10) return false;
	}
	return true;
}

//-----------------------------------------------------------------------------

void ValidRequest::setStringValidate(std::string og, std::string& first, std::string& second)
{
	std::istringstream iss(og);
	std::getline(iss, first);
	std::getline(iss, second);
}

//-----------------------------------------------------------------------------

std::string ValidRequest::error()
{
	return "\n	The Request input is invalid!\n";
}