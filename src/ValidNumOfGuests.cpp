#include "ValidNumOfGuests.h"
#include "BookingForm.h"

//-----------------------------------------------------------------------------

bool ValidNumOfGuests::validate(int numOfGuests, const BookingForm* form)
{
	if (!(numOfGuests > 0 && numOfGuests < 16)) return false;

	auto vecNames = form->getVectorTypes();
	auto fieldCheck = form->getValidateName();
	int switchCaseValue = -1;

	for (int index = 0; index < vecNames.size(); ++index)
	{
		if (vecNames[index] == fieldCheck)
		{
			switchCaseValue = index;
			break;
		}
	}
	return checkCases(numOfGuests, switchCaseValue + 1);
}

//-----------------------------------------------------------------------------

bool ValidNumOfGuests::checkCases(int numOfGuests, int switchCaseValue)
{
	switch (switchCaseValue)
	{
	case SINGLE_ROOM:
		return numOfGuests == SINGLE_ROOM;
	case DOUBLE_ROOM:
		return numOfGuests == DOUBLE_ROOM;
	case PRESIDENTIAL_SUITE_ROOM:
		return numOfGuests < MAX_PRESIDENTIAL_SUITE;
	}
	return true;
}

//-----------------------------------------------------------------------------

std::string ValidNumOfGuests::error()
{
	return "\n	Number of guests input is invalid! \n";
}