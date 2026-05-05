#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <filesystem>

#include "Rule.h"
#include "Parser.h"
#include "Graph.h"
#include "Builder.h"

int main(int argc, char* argv[])
{
	std::string makefilePath = "Makefile";
	std::string requestedTarget;

	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i];
		if (arg == "-f" && i + 1 < argc)
			makefilePath = argv[++i];
		else
			requestedTarget = arg;
	}

	// 1. Parse
	std::vector<Rule> rules = parseMakeFile(makefilePath);
	if (rules.empty()) {
		std::cerr << "mymake: *** No targets. Stop.\n";
		return 1;
	}

	std::unordered_map<std::string, Rule*> ruleMap;	// target -> rule
	for (auto& rule : rules)
		ruleMap[rule.target] = &rule;

	if (requestedTarget.empty())
		requestedTarget = rules[0].target;

	if (ruleMap.find(requestedTarget) == ruleMap.end()) {
		std::cerr << "mymake: *** No rule to make target '" << requestedTarget << "'. Stop.\n";
		return 1;
	}

	// 2. Collect only the rules reachable from the requested target
	std::vector<Rule> relevantRules;
	std::unordered_set<std::string> visited;
	std::queue<std::string> toVisit;
	toVisit.push(requestedTarget);
	visited.insert(requestedTarget);

	while (!toVisit.empty()) {
		std::string current = toVisit.front();
		toVisit.pop();

		auto it = ruleMap.find(current);
		if (it != ruleMap.end()) {
			relevantRules.push_back(*(it->second));
			for (const auto& dep : it->second->dependencies) {
				if (visited.find(dep) == visited.end())	{
					visited.insert(dep);
					toVisit.push(dep);
				}
			}
		}
	}

	// 3. Build dependency graph 
	std::unordered_map<std::string, std::vector<std::string>> adj;
	std::unordered_map<std::string, int> inDegree;
	std::unordered_set<std::string> allNodes;

	buildGraph(relevantRules, adj, inDegree, allNodes);

	// 4. Topological sort
	std::vector<std::string> buildOrder = topologicalSort(adj, inDegree, allNodes);

	// 5. Execute
	bool somethingBuilt = executeBuild(buildOrder, ruleMap);

	if (!somethingBuilt) {
		auto it = ruleMap.find(requestedTarget);
		bool targetExists = (it == ruleMap.end()) || std::filesystem::exists(requestedTarget);
		if (targetExists)
			std::cout << "mymake: '" << requestedTarget << "' is up to date.\n";
		else
			return 1;  // build error already reported
	}

	return 0;
}