#pragma once
#include "TaskStatus.h"
#include "String.h"

class Utility
{
public:
	static constexpr unsigned MAX_BUFF_LENGTH = 1024;
	static const char* getStatus(Status status);
	static bool isDigit(char ch);
	static bool isNumber(const char* str);
	static unsigned convertCharToDigit(char ch);
	static unsigned convertStrToUnsigned(const char* str);
	static bool isDate(const String& str);
	static bool pastDate(const std::tm* currentDate, const std::tm* comparedDate);
	static void formatTmTypeDate(const String& date, std::tm& formatedDate);
};