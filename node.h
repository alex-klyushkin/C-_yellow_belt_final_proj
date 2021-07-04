#pragma once

#include <string>
#include <memory>
#include "date.h"


enum class LogicalOperation
{
	Or,
	And,
};


enum class Comparison
{
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};


class Node {
public:
  virtual int Evaluate(const Date& d, const std::string& str) const = 0;
  virtual ~Node() {}
};


class EmptyNode : public Node
{
public:
	int Evaluate(const Date& d, const std::string& str) const override { return 1; }
};


class DateComparisonNode : public Node
{
public:
	DateComparisonNode(const Comparison& cmp, const Date& date)
		: cmp_(cmp)
		, leftDate_(date)
	{}

	int Evaluate(const Date& d, const std::string& str) const override;

private:
	Comparison cmp_;
	Date leftDate_;
};


class EventComparisonNode : public Node
{
public:
	EventComparisonNode(const Comparison& cmp, const std::string& event)
		: cmp_(cmp)
		, event_(event)
	{}

	int Evaluate(const Date& d, const std::string& str) const override;

private:
	Comparison cmp_;
	std::string event_;
};


class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(const LogicalOperation& op, const std::shared_ptr<Node>& left, const std::shared_ptr<Node>& right)
		: op_(op)
		, left_(left)
		, right_(right)
	{}

	int Evaluate(const Date& d, const std::string& str) const override;

private:
	LogicalOperation op_;
	std::shared_ptr<Node> left_;
	std::shared_ptr<Node> right_;
};
