# Monopoly Board Loader (C)

A C program that loads property and board data for a Monopoly-style game from text files, builds the board structure, and prints it in formatted output. Demonstrates structs, enums, arrays, pointers, and file I/O in C.

## Features

- Loads property definitions (name, price, color) from a text file
- Loads board layout (sequence of space types) from a text file
- Maps properties onto board spaces using pointers
- Falls back to default built-in properties when no file is given
- Validates input and reports errors without crashing

## Build

```bash
gcc main.c monopoly.c -o monopoly
```

## Usage

```bash
./monopoly -t properties.txt -b board.txt
```

| Flag | Description |
|------|-------------|
| `-t FILE` | Load properties from FILE instead of the built-in default list |
| `-b FILE` | Load board layout from FILE and print the resulting board |

- If only `-t` is given, the loaded property list is printed.
- If only `-b` is given, the board is printed using default properties.
- If both `-t` and `-b` are given, only the board is printed.
- If neither flag is given, the program prints nothing.

## Input format

**Properties file** — grouped by color blocks:
```
[Purple]
"LIBRARY":2
"MUSEUM":3

[Green]
"HOSPITAL":5
```

**Board file** — number of spaces on the first line, followed by one space type per line:
```
15
START
PROPERTY
PROPERTY
GO_TO_JAIL
...
```

## Output examples

Property listing:
```
LIBRARY 2 Purple
```

Board listing:
```
1.  START
14. HOSPITAL 5 Green
```

## Error handling

| Code | Meaning |
|------|---------|
| `E1` | A given file could not be opened |
| `E2` | The board references more properties than are available |

## File structure

```
.
├── main.c          # entry point, argument parsing, dispatch logic
├── monopoly.c       # core logic: parsing, board construction, printing
├── monopoly.h       # struct/enum definitions, function declarations
└── CMakeLists.txt
```
