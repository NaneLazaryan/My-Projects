
#include "Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

std::string trim(const std::string& s)
{
	size_t start = s.find_first_not_of(" \t\r\n");
	if (start == std::string::npos) return "";
	size_t end = s.find_last_not_of(" \t\r\n");
	return s.substr(start, end - start + 1);
}

std::vector<std::string> splitWhitespace(const std::string& s)
{
	std::vector<std::string> tokens;
	std::istringstream iss(s);
	std::string token;
	while (iss >> token)
		tokens.push_back(token);
	return tokens;
}

std::vector<Rule> parseMakeFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "mymake: *** Could not open '" << filename << "'. Stop.\n";
		std::exit(1);
	}

	std::vector<Rule> rules;
	std::string line;


	while (std::getline(file, line)) {
		// Command
		if (!line.empty() && line[0] == '\t') {
			std::string cmd = trim(line);
			if (cmd.empty()) continue;  // blank tab line
			if (rules.empty()) {
				std::cerr << "mymake: *** command before first target. Stop.\n";
				std::exit(1);
			}
			rules.back().commands.push_back(cmd);
			continue;
		}

		std::string trimed = trim(line);

		// Skip blank and comments
		if (trimed.empty() || trimed[0] == '#')
			continue;

		// Targer line
		size_t colon = line.find(":");
		if (colon == std::string::npos) {
			std::cerr << "mymake: *** missing separator (':') in line: " << line << ". Stop.\n";
			std::exit(1);
		}

		Rule rule;
		rule.target = trim(line.substr(0, colon));
		std::string depsStr = line.substr(colon + 1);
		rule.dependencies = splitWhitespace(depsStr);

		rules.push_back(rule);
	}

	return rules;
}