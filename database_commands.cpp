
#include <string>
#include <sstream>
#include <iostream>
#include <iterator>
#include "database_commands.h"
#include "database.h"
#include "condition_parser.h"
using namespace std;


unique_ptr<DatabaseCmd> GetCmdByName(const string& cmdName)
{
	if (cmdName == "Add")   return make_unique<AddCmd>();
	if (cmdName == "Print") return make_unique<PrintCmd>();
	if (cmdName == "Find")  return make_unique<FindCmd>();
	if (cmdName == "Del")   return make_unique<DeleteCmd>();
	if (cmdName == "Last")  return make_unique<LastCmd>();

	throw logic_error("Unknown command: " + cmdName);
}


void ProcessInput(Database& db, istream& is, ostream& os)
{
	for (string line; getline(is, line); ) {
		istringstream inp(line);
	    string command;
	    inp >> command;
	    if (!command.empty()) {
	    	auto cmdPtr = GetCmdByName(command);
	    	cmdPtr->GetArgs(inp);
	    	cmdPtr->Exec(db, os);
	    }
	}
}


void AddCmd::GetArgs(std::istream& is)
{
	d = ParseDate(is);
	event = ParseEvent(is);
}


void AddCmd::Exec(Database& db, std::ostream& os) const
{
	db.Add(d, event);
}


void DeleteCmd::Exec(Database& db, std::ostream& os) const
{
    auto predicate = [this](const Date& date, const string& event) {
      return cond->Evaluate(date, event);
    };
    os << "Removed " << db.RemoveIf(predicate) << " entries" << endl;
}


void DeleteCmd::GetArgs(std::istream& is)
{
	cond = ParseCondition(is);
}


void FindCmd::Exec(Database& db, std::ostream& os) const
{
    auto predicate = [this](const Date& date, const string& event) {
      return cond->Evaluate(date, event);
    };

    const auto entries = db.FindIf(predicate);
	for (const auto& ent : entries) {
		os << ent << std::endl;
	}
    os << "Found " << entries.size() << " entries" << endl;
}


void FindCmd::GetArgs(std::istream& is)
{
	cond = ParseCondition(is);
}


void LastCmd::Exec(Database& db, std::ostream& os) const
{
    try {
        os << db.Last(dt) << endl;
    } catch (invalid_argument&) {
        os << "No entries" << endl;
    }
}


void LastCmd::GetArgs(std::istream& is)
{
	dt = ParseDate(is);
}
