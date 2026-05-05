#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Rule.h"


void buildGraph(const std::vector<Rule>& rules,
	std::unordered_map<std::string, std::vector<std::string>>& adj,	 // dependency → target
	std::unordered_map<std::string, int>& inDegree,	// how many deps point INTO this node	
	std::unordered_set<std::string>& allNodes);
std::vector<std::string> topologicalSort(const std::unordered_map<std::string, std::vector<std::string>>& adj,
	std::unordered_map<std::string, int> inDegree,
	const std::unordered_set<std::string>& allNodes);