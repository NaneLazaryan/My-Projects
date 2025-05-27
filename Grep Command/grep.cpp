#include "grep.h"

void grep::printUsage() const {
	std::cout << "Usage: grep <options> <pattern> <files>" << std::endl;
	std::cout << "Example: grep \"hello\" input.txt" << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "  -l    Display list of a filenames only" << std::endl;
	std::cout << "  -i    Ignore case distinctions" << std::endl;
	std::cout << "  -v    Print out all the lines that do not matches the pattern" << std::endl;
	std::cout << "  -f    Take patterns from file, one per line" << std::endl;
	std::cout << "  -c    Count matching lines" << std::endl;
	std::cout << "  -h    Display the matched lines, but do not display the filenames" << std::endl;
	std::cout << "  -n    Display the matched lines and their line numbers" << std::endl;
	std::cout << "  -r    Recursively search directories" << std::endl;
	std::cout << "  -E    Use extended regular expressions" << std::endl;
}

// Highlight part that matches the search 
std::string grep::highlightMatch(const std::string& line, const std::regex& pattern) const {
	std::string result = line;
	std::smatch match;
	std::string::const_iterator searchStart(line.cbegin());

	while (std::regex_search(searchStart, line.cend(), match, pattern)) {
		size_t pos = searchStart - line.cbegin();
		result.insert(pos + match.position() + match.length(), RESET); // Inserts RESET color after the matched text
		result.insert(pos + match.position(), RED);  // Inserts RED color before the matched text
		searchStart = match.suffix().first;
	}

	return result;
}

// Parses the command
void grep::parseArgs(int argc, char* argv[]) {
	int count = parseOptions(argc, argv);
	if (count == -1) return;

	// Parse patterns
	if (options.patterns.empty()) {
		if (count + 1 >= argc) {
			std::cerr << "Missing pattern or filename" << std::endl;
			printUsage();
			return;
		}
		options.patterns.push_back(argv[count++]);
	}

	// Parse files
	for (int i = count; i < argc; i++) {
		options.files.push_back(argv[i]);
	}
}

int grep::parseOptions(int argc, char* argv[]) {
	int count = 1;
	// Parse options
	while (count < argc && argv[count][0] == '-') {
		switch (argv[count][1]) {
		case 'c':
			options.lines_count_only = 1;
			break;
		case 'h':
			options.no_filenames = 1;
			break;
		case 'l':
			options.only_filenames = 1;
			break;
		case 'v':
			options.invert = 1;
			break;
		case 'n':
			options.lines_num = 1;
			break;
		case 'i':
			options.ignore_case = 1;
			break;
		case 'r':
			options.recursive_search = 1;
			break;
		case 'E':
			options.extended_regex = 1;
			break;
		case 'f':
			options.patternFile = argv[++count];
			options.patterns = patternsFromFile(options.patternFile);
			if (options.patterns.empty()) {
				std::cerr << "Error: No patterns found in file " << options.patternFile << std::endl;
				return -1;
			}
			break;
		default:
			std::cerr << "Invalid option: " << argv[count] << std::endl;
			printUsage();
			return -1;
		}
		count++;
	}

	return count;
}

// Function to take patterns from given file: -f option
std::vector<std::string> grep::patternsFromFile(const std::string& filename) const {
	std::vector<std::string> patterns;
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Error: Could not open pattern file " << filename << std::endl;
		return patterns;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (!line.empty()) patterns.push_back(line);
	}

	return patterns;
}

std::string grep::parsePattern(const std::string& pattern) const {
	if (!options.extended_regex) {
		std::string result = pattern;
		const char* specialChars = "+?{}|()";
		
		for (size_t i = 0; i < result.size(); i++) {
			if (result[i] == '\\' ) {
				if (result[i + 1] == '\\') result.erase(i, 1);
				result.erase(i, 1);
				i++;
				continue;
			}
			
			for (const char* c = specialChars; *c != '\0'; c++) {
				if (result[i] == *c) {
					// Insert backslash before the special character
					result.insert(i, "\\");
					i++;
					break;
				}
			}
		}
		return result;
	}
	
	return pattern;
}

void grep::searchFile(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error: Unable to open file " << filename << std::endl;
		return;
	}

	std::string line;
	std::regex::flag_type flag = std::regex::ECMAScript;

	if (options.ignore_case) {
		flag |= std::regex::icase;
	}

	std::vector<std::regex> regexPatterns;
	for (const auto& pattern : options.patterns) {
		std::string parsedPattern = parsePattern(pattern);
		try {
			regexPatterns.emplace_back(parsedPattern, flag);
		}
		catch (const std::regex_error&) {
			std::cerr << "Invalid regex pattern: " << parsedPattern << std::endl;
			return;
		}
	}

	int lineNumber = 1;
	int matchCount = 0;

	while (std::getline(file, line)) {
		bool isMatch = false;
		const std::regex* matchedPattern = nullptr;

		for (const auto& pattern : regexPatterns) {
			if (std::regex_search(line, pattern)) {
				isMatch = true;
				matchedPattern = &pattern;
				break;
			}
		}

		if (options.invert) {
			isMatch = !isMatch;
		}

		if (isMatch) {
			matchCount++;
			if (!options.lines_count_only && !options.only_filenames) {
				if (!options.no_filenames && !options.lines_num) {
					std::cout << GREEN << filename << ": " << lineNumber << ": " << RESET << " ";
				}
				else if (options.lines_num) {
					std::cout << GREEN << lineNumber << ": " << RESET << " ";
				}

				if (matchedPattern) {
					std::cout << highlightMatch(line, *matchedPattern) << std::endl;
				}
				else {
					std::cout << line << std::endl;
				}
			}
		}
		lineNumber++;
	}

	if (options.lines_count_only) {
		std::cout << filename << ": " << matchCount << std::endl;
	}
	else if (options.only_filenames && matchCount > 0) {
		std::cout << filename << std::endl;
	}
}

// Search with option -r
void grep::searchWithPath(const std::string& filePath) {
	fs::path fsPath(filePath);
	if (!fs::exists(fsPath)) {
		std::cerr << "Error: Path does not exist: " << filePath << std::endl;
		return;
	}

	if (fs::is_regular_file(fsPath)) {
		searchFile(filePath);
	}
	else if (fs::is_directory(fsPath)) {
		for (const auto& entry : fs::recursive_directory_iterator(fsPath)) {
			if (entry.is_regular_file()) {
				searchFile(entry.path().string());
			}
		}
	}
	else {
		std::cerr << "Warning: Skipping non-regular file: " << filePath << std::endl;
	}
}
