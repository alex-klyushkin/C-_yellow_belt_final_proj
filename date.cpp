
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


void DataTestInput()
{
	istringstream input("2017-05-2 0001-1-1 0-1-31 0000-2-2");
	Date d1, d2, d3, d4;
	input >> d1 >> d2 >> d3 >> d4;
	AssertEqual(d1, Date{2017, 5, 2}, "DataTestInput1");
	AssertEqual(d2, Date{1, 1, 1}, "DataTestInput2");
	AssertEqual(d3, Date{0, 1, 31}, "DataTestInput3");
	AssertEqual(d4, Date{0, 2, 2}, "DataTestInput4");
}


void DataTestOutput()
{
	Date d1{2017, 5, 2};
	Date d2{1, 1, 1};
	Date d3{0, 1, 31};
	Date d4{0, 2, 2};
	ostringstream output;

	output << d1;
	AssertEqual(output.str(), "2017-05-02", "DateTestOutput1");
	output.str("");

	output << d2;
	AssertEqual(output.str(), "0001-01-01", "DateTestOutput2");
	output.str("");

	output << d3;
	AssertEqual(output.str(), "0000-01-31", "DateTestOutput3");
	output.str("");

	output << d4;
	AssertEqual(output.str(), "0000-02-02", "DateTestOutput4");
	output.str("");
}
