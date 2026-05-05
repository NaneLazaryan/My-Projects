# mymake
A minimal `make` utility implemented in C++17. Parses a Makefile, builds a dependency graph, resolves build order via topological sort, and executes only the targets that are out of date — mirroring the core behavior of GNU Make.

---

## Features

- Makefile parsing (targets, dependencies, tab-indented commands)
- Dependency graph construction and **topological sort** for correct build ordering
- **Incremental builds** — skips targets whose dependencies haven't changed (filesystem timestamp comparison)
- **Circular dependency detection** with an explicit error and exit
- Reachability pruning — only rules relevant to the requested target are processed
- Custom Makefile path via `-f`
- Defaults to the first target in the file when none is specified
- Error reporting consistent with GNU Make conventions (`*** ... Stop.`)

---

## Build

Requires a C++17-compatible compiler.

```bash
g++ -std=c++17 -o mymake main.cpp Parser.cpp Graph.cpp Builder.cpp
```

---

## Usage

```bash
mymake [options] [target]
```

| Argument | Description |
|----------|-------------|
| `target` | Target to build (defaults to first target in Makefile) |
| `-f <file>` | Use a custom Makefile path (defaults to `./Makefile`) |

### Examples

Build the default target:
```bash
./mymake
```

Build a specific target:
```bash
./mymake main
```

Use a custom Makefile:
```bash
./mymake -f build/MyMakefile all
```

---

## How It Works

```
Makefile
   │
   ▼
[Parser]  →  list of Rules (target, dependencies, commands)
   │
   ▼
[Graph]   →  adjacency list + in-degree map → topological sort
   │
   ▼
[Builder] →  timestamp comparison → execute shell commands in order
```

1. **Parse** — reads the Makefile line by line; tab-prefixed lines are commands, colon lines are rules.
2. **Reachability** — BFS from the requested target discards irrelevant rules.
3. **Graph** — builds a directed graph where edges go from dependency → target.
4. **Topological sort** — Kahn's algorithm produces a valid build order; exits on cycle detection.
5. **Execute** — for each target in order, compares filesystem timestamps and runs commands only when a rebuild is needed.

---

## Project Structure

```
.
├── main.cpp       # Entry point: argument parsing, pipeline orchestration
├── Rule.h         # Rule struct (target, dependencies, commands)
├── Parser.h/.cpp  # Makefile parser
├── Graph.h/.cpp   # Dependency graph construction and topological sort
└── Builder.h/.cpp # Timestamp-based rebuild logic and command execution
```

---

## Supported Makefile Syntax

```makefile
target: dep1 dep2
	command1
	command2

dep1:
	command3
```

- Targets and dependencies on a single colon-separated line
- Commands must be indented with a **tab** (not spaces)
- Lines starting with `#` are treated as comments
