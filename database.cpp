
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
	if (!events.eventsSet.count(event)) {
		events.eventsVec.push_back(event);
		auto res = events.eventsSet.insert(event);
		if (!res.second) throw logic_error("Add: duplicate");
	}
}


void Database::Print(ostream& os) const
{
	for (const auto& [date, events] : database_) {
		for (const auto& event : events.eventsVec) {
			os << date << " " << event << endl;
		}
	}
}


pair<Date, string> Database::Last(const Date& d) const
{
	auto it = database_.upper_bound(d);
	if (it == database_.cbegin()) {
		throw std::invalid_argument("");
	}

	it = prev(it);
	return make_pair(it->first, it->second.eventsVec.back());
}
