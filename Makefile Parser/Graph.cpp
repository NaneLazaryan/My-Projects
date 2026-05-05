#include "Graph.h"
#include <iostream>
#include <queue>
#include <cstdlib>

void buildGraph(const std::vector<Rule>& rules,
	std::unordered_map<std::string, std::vector<std::string>>& adj,	 // dependency → target
	std::unordered_map<std::string, int>& inDegree,	// how many deps point INTO this node	
	std::unordered_set<std::string>& allNodes)
{
	for (const auto& rule : rules) {
		allNodes.insert(rule.target);
		if (inDegree.find(rule.target) == inDegree.end())
			inDegree[rule.target] = 0;

		for (const auto& dep : rule.dependencies) {
			allNodes.insert(dep);
			adj[dep].push_back(rule.target);
			inDegree[rule.target]++;
			if (inDegree.find(dep) == inDegree.end())
				inDegree[dep] = 0;
		}
	}
}

std::vector<std::string> topologicalSort(const std::unordered_map<std::string, std::vector<std::string>>& adj,
	std::unordered_map<std::string, int> inDegree,
	const std::unordered_set<std::string>& allNodes)
{
	std::queue<std::string> q;
	// starts with 0 degree
	for (const auto& node : allNodes) {
		if (inDegree[node] == 0) {
			q.push(node);
		}
	}

	std::vector<std::string> sorted;
	while (!q.empty()) {
		std::string current = q.front();
		q.pop();
		sorted.push_back(current);

		auto it = adj.find(current);
		if (it != adj.end()) {
			for (const auto& neighbor : it->second) {
				inDegree[neighbor]--;
				// Add to queue if it doesn't have unprocessed dependency, so it can be processed
				if (inDegree[neighbor] == 0)
					q.push(neighbor);
			}
		}
	}

	if (sorted.size() != allNodes.size()) {
		std::cerr << "mymake: *** circular dependency detected. Stop.\n";
		std::exit(1);
	}

	return sorted;
}