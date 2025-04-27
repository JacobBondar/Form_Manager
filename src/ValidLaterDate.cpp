#include "ValidLaterDate.h"
#include "ValidDate.h"
#include "BookingForm.h"

//-----------------------------------------------------------------------------

bool ValidLaterDate::validate(const std::string& date, BookingForm* form)
{
	if (!ValidDate::validate(date, form)) return false;
	auto prev = form->getCompareField();

	std::string prevYear, prevMonth, prevDay, thisYear, thisMonth, thisDay;

	getDateValues(prev, prevYear, prevMonth, prevDay);
	getDateValues(date, thisYear, thisMonth, thisDay);

	return compareDates(prevYear, prevMonth, prevDay, thisYear, thisMonth, thisDay);
}

//-----------------------------------------------------------------------------

void ValidLaterDate::getDateValues(const std::string& date, std::string& year, 
								   std::string& month, std::string& day)
{
	year = date.substr(0, 4);
	month = date.substr(5, 2);
	day = date.substr(8, 2);
}

//-----------------------------------------------------------------------------

bool ValidLaterDate::compareDates(std::string prevYear, std::string prevMonth, 
								  std::string prevDay, std::string thisYear, 
								  std::string thisMonth, std::string thisDay)
{
	if (prevYear <= thisYear)
	{
		if (prevYear < thisYear) return true;

		if (prevMonth <= thisMonth)
		{
			if (prevMonth < thisMonth) return true;

			if (prevDay <= thisDay)
			{
				return true;
			}
		}
	}
	return false;
}

//-----------------------------------------------------------------------------

std::string ValidLaterDate::error()
{
	return "\n	The Date input is invalid!\n";
}