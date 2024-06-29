#include "Utility.h"
#include <stdexcept>
#include "String.h"
#include "sstream"
#include <iomanip>
#include <fstream>

const char* Utility::getStatus(Status status)
{
	switch (status)
	{
	case ON_HOLD:
		return "ON_HOLD";
		break;
	case IN_PROCESS:
		return "IN_PROCESS";
		break;
	case DONE:
		return "DONE";
		break;
	case OVERDUE:
		return "OVERDUE";
		break;
	default:
		return "";
		break;
	}
}

bool Utility::isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

bool Utility::isNumber(const char* str)
{
	if (!str)
	{
		throw std::invalid_argument("Submitted task must be non-null");
	}

	while (*str)
	{
		if (!isDigit(*str))
		{
			return false;
		}
		str++;
	}

	return true;
}

unsigned Utility::convertCharToDigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return ch - '0';

	return -1;
}

unsigned Utility::convertStrToUnsigned(const char* str)
{
	if (!str)
		return 0;

	unsigned result = 0;
	while (*str)
	{
		int digit = convertCharToDigit(*str);
		if (digit == -1)
			return 0;
		(result *= 10) += digit;
		str++;
	}
	return result;
}

bool Utility::isDate(const String& str)
{
	unsigned size = str.getSize();

	for (size_t i = 0; i < size; i++)
	{
		if (!isDigit(str[i]) && str[i] != '-')
		{
			return false;
		}
	}

	return true;
}

bool Utility::pastDate(const std::tm* currentDate, const std::tm* comparedDate)
{
	if (currentDate->tm_year > comparedDate->tm_year)
	{
		return true;
	}
	if (currentDate->tm_year < comparedDate->tm_year)
	{
		return false;
	}
	if (currentDate->tm_mon > comparedDate->tm_mon)
	{
		return true;
	}
	if (currentDate->tm_mon < comparedDate->tm_mon)
	{
		return false;
	}
	if (currentDate->tm_mday > comparedDate->tm_mday)
	{
		return true;
	}

	return false;
}

void Utility::formatTmTypeDate(const String& date, std::tm& formatedDate)
{
	std::stringstream ss(date.c_str());
	ss >> std::get_time(&formatedDate, "%Y-%m-%d");
}

void Utility::loadStringFromFile(std::ifstream& ifs, String& string)
{
	size_t size = 0;
	ifs.read(reinterpret_cast<char*>(&size), sizeof(size_t));
	char* currentUsername = new char[size + 1];
	ifs.read((char*)(&*currentUsername), size + 1);
	string = currentUsername;
	delete currentUsername;
}
