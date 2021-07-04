#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <memory>
#include <set>
#include "date.h"


std::ostream& operator<<(std::ostream& os, const std::pair<Date, std::string>& p);


using StrSharedPtr = std::shared_ptr<std::string>;

struct DatabaseComp
{
	bool operator()(const StrSharedPtr& lhs, const StrSharedPtr& rhs) const
	{
		return *lhs < *rhs;
	}
};


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
			// move elements for deleting to end of vector
			auto vecIt = std::stable_partition(eventsVec.begin(), eventsVec.end(), [&dt, &pred](const StrSharedPtr& ev) { return !pred(dt, *ev); });

			// sync set with vector
			for (auto it = vecIt; it != eventsVec.end(); ++it) {
				eventsSet.erase(*it);
			}

			count += std::distance(vecIt, eventsVec.end());
			eventsVec.erase(vecIt, eventsVec.end());

			if (eventsVec.empty()) {
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
				if (p(date, *event)) {
					out.push_back(std::make_pair(date, *event));
				}
			}
		}
		return out;
	}

private:
	struct Events
	{
		std::set<StrSharedPtr, DatabaseComp> eventsSet;
		std::vector<StrSharedPtr> eventsVec;
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
