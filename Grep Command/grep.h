#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// ANSI escape codes for colors
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";

class grep {
public:
	struct Options {
		bool lines_count_only = false; // -c
		bool ignore_case = false;      // -i
		bool invert = false;           // -v
		bool lines_num = false;        // -n
		bool no_filenames = false;     // -h
		bool only_filenames = false;   // -l
		bool recursive_search = false; // -r
		bool extended_regex = false;   // -E
		std::string patternFile;       // -f
		std::vector<std::string> patterns;
		std::vector<std::string> files;
	};
	Options options;

	grep() = default;
	~grep() = default;

	void printUsage() const;
	std::string highlightMatch(const std::string& line, const std::regex& pattern) const;
	
	std::vector<std::string> patternsFromFile(const std::string& filename) const;
	std::string parsePattern(const std::string& pattern) const;

	void parseArgs(int argc, char* argv[]);
	int parseOptions(int argc, char* argv[]);

	void searchFile(const std::string& filename);
	void searchWithPath(const std::string& filePath);
};
