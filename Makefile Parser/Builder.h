#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Rule.h"

bool needsRebuild(const std::string& target, const std::vector<std::string>& deps, bool& fatalError);
bool executeBuild(const std::vector<std::string>& buildOrder, const std::unordered_map<std::string, Rule*>& ruleMap);