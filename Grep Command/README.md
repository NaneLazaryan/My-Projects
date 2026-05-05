# grep
A command-line search tool implemented in C++ that replicates core functionality of the Unix `grep` utility. Supports regular expression matching, recursive directory search, colorized output, and multiple search flags.

---

## Features

- Pattern matching using ECMAScript regular expressions
- Extended regex support (`-E`)
- Case-insensitive search (`-i`)
- Inverted matching — print non-matching lines (`-v`)
- Recursive directory traversal (`-r`)
- Line number display (`-n`)
- Match count per file (`-c`)
- Filename-only output (`-l`)
- Suppress filename in output (`-h`)
- Load patterns from a file (`-f`)
- **Colorized output** — matched text highlighted in red, filename/line info in green

---

## Build

Requires a C++17-compatible compiler (GCC, Clang, or MSVC).

```bash
g++ -std=c++17 -o grep main.cpp grep.cpp
```

On Windows, ANSI color output is enabled automatically via the Windows Console API.

---

## Usage

```
grep <options> <pattern> <file(s)>
```

### Options

| Flag | Description |
|------|-------------|
| `-i` | Ignore case distinctions |
| `-v` | Print lines that do **not** match the pattern |
| `-n` | Display matched lines with their line numbers |
| `-c` | Count matching lines per file |
| `-l` | Print only the names of files with matches |
| `-h` | Print matched lines without filenames |
| `-r` | Recursively search directories |
| `-E` | Use extended regular expressions |
| `-f <file>` | Read patterns from a file (one per line) |

---

## Examples

Search for a pattern in a file:
```bash
./grep "hello" input.txt
```

Case-insensitive search across multiple files:
```bash
./grep -i "error" log1.txt log2.txt
```

Show line numbers for matches:
```bash
./grep -n "TODO" main.cpp
```

Recursively search a directory:
```bash
./grep -r "main" ./src
```

Use extended regex:
```bash
./grep -E "foo|bar" input.txt
```

Load patterns from a file:
```bash
./grep -f patterns.txt input.txt
```

Count matches per file:
```bash
./grep -c "warning" *.log
```

---

## Project Structure

```
.
├── main.cpp      # Entry point, argument dispatch
├── grep.h        # Class declaration and Options struct
└── grep.cpp      # Core logic: parsing, matching, output
```

---

## Platform Support

| Platform | Status |
|----------|--------|
| Linux    | ✅ Supported |
| macOS    | ✅ Supported |
| Windows  | ✅ Supported (ANSI color via WinAPI) |
