#ifdef _WIN32
#include <windows.h>
#endif

// For colors used in terminal
void enableVirtualTerminal() {
#ifdef _WIN32
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) return;

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode)) return;

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
#endif
}

#include "grep.h"

int main(int argc, char* argv[]) {
	enableVirtualTerminal();

	grep Grep;

	if (argc < 3) {
		Grep.printUsage();
		return 1;
	}

	Grep.parseArgs(argc, argv);
	grep::Options opts = Grep.options;

	for (const auto& file : opts.files) {
		if (opts.recursive_search)
			Grep.searchWithPath(file);
		else
			Grep.searchFile(file);
	}
	return 0;
}
