
#include <sstream>
#include "database_commands.h"
#include "database.h"
#include "test_runner.h"
#include "condition_parser.h"
using namespace std;


static void DatabaseTest(const string& input, const string& forComp, const string& testName)
{
	Database d;
	istringstream inp(input);
	ostringstream outp;

	ProcessInput(d, inp, outp);
	AssertEqual(outp.str(), forComp, testName);
}


void DatabaseTestAdd()
{
	{
		string input(R"test(
				Add 2017-1-1 New Year
				Add 2017-1-1 New Year
				Print)test");
		string forComp("2017-01-01 New Year\n");
		DatabaseTest(input, forComp, "DatabaseTestAdd1");
	}

	{
		string input(R"test(
				Add 2017-1-1 New Year
				Add 2017-1-1 New Year
				Del date == 2017-1-1
				Print)test");
		DatabaseTest(input, "Removed 1 entries\n", "DatabaseTestAdd2");
	}

	{
		string input(R"test(
				Add 2017-1-1 New Year
				Add 2017-1-1 New Year
				Add 2017-1-1 Holyday
				Del date == 2017-1-1 AND event == "New Year"
				Print
				Add 2017-1-1 New Year
				Print)test");
		string forComp("Removed 1 entries\n" "2017-01-01 Holyday\n" "2017-01-01 Holyday\n" "2017-01-01 New Year\n");
		DatabaseTest(input, forComp, "DatabaseTestAdd3");
	}
}


void DatabaseTestPrint()
{
	{
		string input(R"test(
				Add 2017-01-01 Holiday
				Add 2017-03-08 Holiday
				Add 2017-1-1 New Year
				Add 2017-1-1 New Year
				Print
				Del
				Print)test");
		string forComp("2017-01-01 Holiday\n" "2017-01-01 New Year\n" "2017-03-08 Holiday\n" "Removed 3 entries\n");
		DatabaseTest(input, forComp, "DatabaseTestPrint1");
	}

	{
		string input(R"test(
				Print)test");
		DatabaseTest(input, "", "DatabaseTestPrint2");
	}
}


void DatabaseTestFind()
{
	{
		string input(R"test(
				Add 2017-01-01 Holiday
				Add 2017-03-08 Holiday
				Add 2017-01-01 New Year
				Find event != "working day"
				Add 2017-05-09 Holiday)test");
		string forComp("2017-01-01 Holiday\n" "2017-01-01 New Year\n" "2017-03-08 Holiday\n" "Found 3 entries\n");
		DatabaseTest(input, forComp, "DatabaseTestFind1");
	}

	{
		string input(R"test(
				Add 2017-01-01 Holiday
				Add 2017-03-08 Holiday
				Add 2017-01-01 New Year
				Find date == 2017-1-1
				Add 2017-03-07 Holiday
				Find date != 2017-1-1)test");
		string forComp("2017-01-01 Holiday\n" "2017-01-01 New Year\n" "Found 2 entries\n" "2017-03-07 Holiday\n" "2017-03-08 Holiday\n" "Found 2 entries\n");
		DatabaseTest(input, forComp, "DatabaseTestFind2");
	}

	{
		string input(R"test(
				Add 2017-01-01 Holiday
				Add 2017-03-08 Holiday
				Add 2017-1-1 New Year
				Find)test");
		string forComp("2017-01-01 Holiday\n" "2017-01-01 New Year\n" "2017-03-08 Holiday\n" "Found 3 entries\n");
		DatabaseTest(input, forComp, "DatabaseTestFind3");
	}

	{
		string forComp("Found 0 entries\n");
		DatabaseTest("Find", forComp, "DatabaseTestFind4");
	}

	{
		string input2(R"test(
					Add 2017-11-21 meeting
					Add 2017-11-20 meeting
					Add 2017-11-19 meeting
					Find date > 2017-11-19 AND date < 2017-11-21 AND event == "meeting"
					Del  date > 2017-11-19 AND date < 2017-11-21 AND event == "meeting"
					Find date > 2017-11-19 AND date < 2017-11-21 AND event == "meeting")test");
		string forComp2("2017-11-20 meeting\n" "Found 1 entries\n" "Removed 1 entries\n" "Found 0 entries\n");
		DatabaseTest(input2, forComp2, "DatabaseTestFind5");
	}

	{
		string input(R"test(
					Add 2017-11-21 Tuesday
					Del
					Find)test");
		string forComp("Removed 1 entries\n" "Found 0 entries\n");
		DatabaseTest(input, forComp, "DatabaseTestFind6");
	}
}


void DatabaseTestDel()
{
	{
		string input(R"test(
				Add 2017-06-01 1st of June
				Add 2017-07-08 8th of July
				Add 2017-07-08 Someone's birthday
				Del date == 2017-07-08)test");
		string forComp = "Removed 2 entries\n";
		DatabaseTest(input, forComp, "DatabaseTestDel1");
	}

	{
		string input(R"test(
				Add 2017-01-01 Holiday
				Add 2017-03-08 Holiday
				Add 2017-1-1 New Year
				Add 2017-1-1 New Year
				Del)test");
		string forComp("Removed 3 entries\n");
		DatabaseTest(input, forComp, "DatabaseTestDel2");
	}

	{
		string forComp("Removed 0 entries\n");
		DatabaseTest("Del", forComp, "DatabaseTestDel3");
	}

	{
		string input(R"test(
				Add 2017-06-01 1st of June
				Add 2017-07-08 8th of July
				Add 2017-07-08 Someone's birthday
				Del date == 2017-07-11)test");
		string forComp = "Removed 0 entries\n";
		DatabaseTest(input, forComp, "DatabaseTestDel4");
	}

	{
		string input(R"test(
				Add 2017-06-01 1st of June
				Add 2017-07-08 8th of July
				Add 2017-07-08 Someone's birthday
				Del date == 2017-07-08
				Add 2017-07-08 Someone's birthday
				Del date == 2017-07-08)test");
		string forComp("Removed 2 entries\n" "Removed 1 entries\n");
		DatabaseTest(input, forComp, "DatabaseTestDel5");
	}

	{
		string input1(R"test(
					Add 2017-11-21 sport event
					Add 2017-11-20 meeting
					Del date < 2017-12-12 AND (event == "holiday" OR event == "sport event")
					Find)test");
		string forComp1("Removed 1 entries\n" "2017-11-20 meeting\n" "Found 1 entries\n");
		DatabaseTest(input1, forComp1, "DatabaseTestDelComplexCond6");
	}
}


void DatabaseTestLast()
{
	{
		string input(R"test(
				Add 2017-01-01 New Year
				Add 2017-03-08 Holiday
				Add 2017-01-01 Holiday
				Last 2016-12-31
				Last 2017-01-01
				Last 2017-06-01
				Del date == 2017-01-01 AND event == "Holiday"
				Last 2017-01-01
				Last 2017-02-01)test");
		string forComp("No entries\n" "2017-01-01 Holiday\n" "2017-03-08 Holiday\n" "Removed 1 entries\n" "2017-01-01 New Year\n" "2017-01-01 New Year\n");
		DatabaseTest(input, forComp, "DatabaseTestLast1");
	}

	{
		string forComp("No entries\n");
		DatabaseTest("Last 2017-1-1", forComp, "DatabaseTestLast2");
	}
}


void DatabaseTestCommon()
{
	string input(R"test(
				Add 2017-11-21 Tuesday
				Add 2017-11-20 Monday
				Add 2017-11-21 Weekly meeting
				Print
				Find event != "Weekly meeting"
				Last 2017-11-30
				Del date > 2017-11-20
				Last 2017-11-30
				Last 2017-11-01)test");

	string forComp("2017-11-20 Monday\n"
	"2017-11-21 Tuesday\n"
	"2017-11-21 Weekly meeting\n"
	"2017-11-20 Monday\n"
	"2017-11-21 Tuesday\n"
	"Found 2 entries\n"
	"2017-11-21 Weekly meeting\n"
	"Removed 2 entries\n"
	"2017-11-20 Monday\n"
	"No entries\n");

	DatabaseTest(input, forComp, "DatabaseTestCommon");
}
