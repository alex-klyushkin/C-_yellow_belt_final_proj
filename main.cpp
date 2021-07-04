//============================================================================
// Name        : database.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdexcept>
#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"
#include "database_commands.h"
using namespace std;


void TestAll();


int main()
{
  TestAll();

  Database db;
  ProcessInput(db, cin, cout);
}


void TestAll()
{
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");

  tr.RunTest(DatabaseTestAdd, "DatabaseTestAdd");
  tr.RunTest(DatabaseTestPrint, "DatabaseTestPrint");
  tr.RunTest(DatabaseTestFind, "DatabaseTestFind");
  tr.RunTest(DatabaseTestDel, "DatabaseTestDel");
  tr.RunTest(DatabaseTestLast, "DatabaseTestLast");
  tr.RunTest(DatabaseTestCommon, "DatabaseTestCommon");

  tr.RunTest(DateTestComparison, "DateTestComparison");
}
