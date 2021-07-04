
#include "node.h"
using namespace std;


int DateComparisonNode::Evaluate(const Date& d, const std::string& str) const
{
	switch (cmp_)
	{
		case Comparison::Less : 	      return d < leftDate_;
		case Comparison::LessOrEqual :    return d <= leftDate_;
		case Comparison::Greater :        return d > leftDate_;
		case Comparison::GreaterOrEqual : return d >= leftDate_;
		case Comparison::Equal :          return d == leftDate_;
		case Comparison::NotEqual :       return d != leftDate_;
		default : return 0;
	}
}


int EventComparisonNode::Evaluate(const Date& d, const std::string& str) const
{
	switch (cmp_)
	{
		case Comparison::Less : 	      return str < event_;
		case Comparison::LessOrEqual :    return str <= event_;
		case Comparison::Greater :        return str > event_;
		case Comparison::GreaterOrEqual : return str >= event_;
		case Comparison::Equal :          return str == event_;
		case Comparison::NotEqual :       return str != event_;
		default : return 0;
	}
}


int LogicalOperationNode::Evaluate(const Date& d, const std::string& str) const
{
	auto res1 = left_->Evaluate(d, str);
	auto res2 = right_->Evaluate(d, str);
	if (op_ == LogicalOperation::And) {
		return res1 && res2;
	}
	return res1 || res2;
}

