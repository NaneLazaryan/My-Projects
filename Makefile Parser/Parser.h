#pragma once

#include <string>
#include <vector>
#include "Rule.h"


std::string trim(const std::string& s);
std::vector<std::string> splitWhitespace(const std::string& s);
std::vector<Rule> parseMakeFile(const std::string& filename);