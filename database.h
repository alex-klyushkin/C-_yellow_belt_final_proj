#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include "date.h"


std::ostream& operator<<(std::ostream& os, const std::pair<Date, std::string>& p);


class Database
{
public:
	void Add(const Date& d, const std::string& event);
	void Print(std::ostream& os) const;
	std::pair<Date, std::string> Last(const Date& d) const;

	template<typename Pred>
	int RemoveIf(const Pred& pred)
	{
		int count = 0;
		auto dbIt = database_.begin();
		while (dbIt != database_.end()) {
			const auto& dt = dbIt->first;
			auto& events = dbIt->second;
			auto it = remove_if(events.begin(), events.end(), [&dt, &pred](const std::string& ev) { return pred(dt, ev); });
			count += std::distance(it, events.end());
			events.erase(it, events.end());

			if (events.empty()) {
				dbIt = database_.erase(dbIt);
			} else {
				++dbIt;
			}
		}
		return count;
	}

	template<typename Pred>
	std::vector<std::pair<Date, std::string>> FindIf(const Pred& p) const
	{
		std::vector<std::pair<Date, std::string>> out;
		for (const auto& [date, events] : database_) {
			for (const auto& event : events) {
				if (p(date, event)) {
					out.push_back(std::make_pair(date, event));
				}
			}
		}
		return out;
	}

private:
	using DatabaseType = std::map<Date, std::vector<std::string>>;
	DatabaseType database_;
};


void DatabaseTestAdd();
void DatabaseTestPrint();
void DatabaseTestFind();
void DatabaseTestDel();
void DatabaseTestLast();
void DatabaseTestCommon();
