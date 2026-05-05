#include "Builder.h"
#include <iostream>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

// Returns: true = needs rebuild, false = up to date.
bool needsRebuild(const std::string& target, const std::vector<std::string>& deps, bool& fatalError)
{
	fatalError = false;

	// File doesn't exist
	if (!fs::exists(target)) return true;

	auto targetTime = fs::last_write_time(target);

	for (const auto& dep : deps) {
		if (!fs::exists(dep)) {
			std::cerr << "mymake: *** No rule to make target '" << dep
				<< "', needed by '" << target << "'. Stop.\n";
			fatalError = true;
			return false;
		}

		auto depTime = fs::last_write_time(dep);
		if (depTime > targetTime) return true;  // dependency newer than the target
	}

	return false;
}

bool executeBuild(const std::vector<std::string>& buildOrder, const std::unordered_map<std::string, Rule*>& ruleMap)
{
	bool somethingBuilt = false;

	for (const auto& target : buildOrder) {
		auto it = ruleMap.find(target);
		if (it == ruleMap.end()) continue; // source file — no rule, nothing to do

		const Rule& rule = *(it->second);

		bool fatalError = false;
		if (needsRebuild(rule.target, rule.dependencies, fatalError)) {
			for (const auto& cmd : rule.commands) {
				std::cout << cmd << "\n";
				int ret = std::system(cmd.c_str());
				if (ret != 0)
				{
					std::cerr << "mymake: *** [" << rule.target << "] Error " << ret << "\n";
					return false;  // signal failure to caller
				}
			}
			somethingBuilt = true;
		}
		else if (fatalError)
			return false;  // missing dependency
	}

	return somethingBuilt;
}