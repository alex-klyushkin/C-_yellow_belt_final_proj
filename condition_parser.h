#pragma once


#include <iostream>
#include "node.h"


std::shared_ptr<Node> ParseCondition(std::istream& is);
Date ParseDate(std::istream& is);
std::string ParseEvent(std::istream& is);
void TestParseCondition();
void TestParseEvent();
