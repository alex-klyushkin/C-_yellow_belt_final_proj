#pragma once

#include <iostream>

struct Date
{
	int year;
	int mounth;
	int day;
};

std::istream& operator>>(std::istream& is, Date& d);
std::ostream& operator<<(std::ostream& os, const Date& d);

bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);

void DateTestComparison();
