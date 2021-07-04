
#include "database.h"
#include "condition_parser.h"
#include "test_runner.h"
using namespace std;


ostream& operator<<(ostream& os, const pair<Date, string>& p)
{
	os << p.first << " " << p.second;
	return os;
}


void Database::Add(const Date& d, const string& event)
{
	auto& events = database_[d];
	auto ptr = make_shared<string>(event);
	// Has element already been added?
	if (!events.eventsSet.count(ptr)) {
		events.eventsVec.push_back(ptr);
		events.eventsSet.insert(ptr);
	}
}


void Database::Print(ostream& os) const
{
	for (const auto& [date, events] : database_) {
		for (const auto& event : events.eventsVec) {
			os << date << " " << *event << endl;
		}
	}
}


pair<Date, string> Database::Last(const Date& d) const
{
	auto it = database_.upper_bound(d);
	if (it == database_.cbegin()) {
		throw std::invalid_argument("");
	}

	// we need prev elem, because upper_bound finds element which is greater
	it = prev(it);
	return make_pair(it->first, *it->second.eventsVec.back());
}
