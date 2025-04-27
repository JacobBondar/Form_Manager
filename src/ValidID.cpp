#include "ValidID.h"

//-----------------------------------------------------------------------------

bool ValidID::validate(uint32_t id, const BookingForm* form)
{
	if (!checkSize(id)) return false;

	int reviewDigit = id % 10;
	id /= 10;

	int sumDigits = calcSumDigit(id);

	int roundSum = sumDigits % 10 == 0 ? sumDigits : (sumDigits / 10 + 1) * 10;

	if (reviewDigit != roundSum - sumDigits) return false;
	return true;
}

//-----------------------------------------------------------------------------

bool ValidID::checkSize(uint32_t id)
{
	std::string idString = std::to_string(id);
	if (idString.size() != 9) return false;
	return true;
}

//-----------------------------------------------------------------------------

int ValidID::calcSumDigit(int id)
{
	int sumDigits = 0, tempSum, index = 0;
	while (id != 0)
	{
		if (index % 2 != 0) sumDigits += id % 10;
		else
		{
			tempSum = 2 * (id % 10);
			if (tempSum > 9) sumDigits += (tempSum / 10 + tempSum % 10);
			else sumDigits += tempSum;
		}
		id /= 10;
		index++;
	}
	return sumDigits;
}

//-----------------------------------------------------------------------------

std::string ValidID::error()
{
	return "\n	The ID is invalid!\n";
}