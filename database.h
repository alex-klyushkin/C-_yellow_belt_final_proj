#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <memory>
#include <set>
#include <sstream>
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
			auto& eventsVec = dbIt->second.eventsVec;
			auto& eventsSet = dbIt->second.eventsSet;
			auto vecIt = std::stable_partition(eventsVec.begin(), eventsVec.end(), [&dt, &pred](const std::string& ev) { return !pred(dt, ev); });

			for (auto it = vecIt; it != eventsVec.end(); ++it) {
				auto res = eventsSet.erase(*it);
				if (!res) {
					std::ostringstream out;
					out << "vec size " << eventsVec.size() << " set size " << eventsSet.size() << " ";
					for (const auto& str : eventsVec) {
						out << str << " ";
					}
					for (const auto& str : eventsSet) {
						out << str << " ";
					}
					out << "Can't erase elem from set: " << *it;
					throw std::logic_error(out.str());
				}
			}

			count += std::distance(vecIt, eventsVec.end());
			eventsVec.erase(vecIt, eventsVec.end());

			if (eventsVec.empty()) {
				if (!eventsSet.empty()) {
					std::ostringstream out;
					out << eventsSet.size();
					throw std::logic_error(out.str());
				}
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
			for (const auto& event : events.eventsVec) {
				if (p(date, event)) {
					out.push_back(std::make_pair(date, event));
				}
			}
		}
		return out;
	}

private:
	struct Events
	{
		std::set<std::string> eventsSet;
		std::vector<std::string> eventsVec;
	};
	using DatabaseType = std::map<Date, Events>;
	DatabaseType database_;
};


void DatabaseTestAdd();
void DatabaseTestPrint();
void DatabaseTestFind();
void DatabaseTestDel();
void DatabaseTestLast();
void DatabaseTestCommon();
