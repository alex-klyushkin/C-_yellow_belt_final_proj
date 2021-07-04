
#include <tuple>
#include <iomanip>
#include "date.h"
#include "test_runner.h"
using namespace std;


istream& operator>>(istream& is, Date& d)
{
	is >> d.year;
	is.ignore(1);
	is >> d.mounth;
	is.ignore(1);
	is >> d.day;

	return is;
}


std::ostream& operator<<(std::ostream& os, const Date& d)
{
	os << std::setw(4) << setfill('0') << d.year << "-" << std::setw(2) << setfill('0') << d.mounth << "-" << std::setw(2) << setfill('0') << d.day;
	return os;
}


bool operator<(const Date& lhs, const Date& rhs)
{
	return tie(lhs.year, lhs.mounth, lhs.day) < tie(rhs.year, rhs.mounth, rhs.day);
}


bool operator==(const Date& lhs, const Date& rhs)
{
	return tie(lhs.year, lhs.mounth, lhs.day) == tie(rhs.year, rhs.mounth, rhs.day);
}


bool operator<=(const Date& lhs, const Date& rhs)
{
	return lhs < rhs || lhs == rhs;
}


bool operator>(const Date& lhs, const Date& rhs)
{
	return !(lhs <= rhs);
}


bool operator>=(const Date& lhs, const Date& rhs)
{
	return !(lhs < rhs);
}


bool operator!=(const Date& lhs, const Date& rhs)
{
	return !(lhs == rhs);
}


void DateTestComparison()
{
	Date d1{2017, 01, 01};
	Date d2{2017, 01, 02};

	Assert(d1 == d1, "DateTestComparison1");
	Assert(d1 != d2, "DateTestComparison2");
	Assert(d1 < d2, "DateTestComparison3");
	Assert(d1 <= d2, "DateTestComparison4");
	Assert(d1 <= d1, "DateTestComparison5");
	Assert(d2 > d1, "DateTestComparison6");
	Assert(d2 >= d1, "DateTestComparison7");
	Assert(d1 >= d1, "DateTestComparison8");
}

