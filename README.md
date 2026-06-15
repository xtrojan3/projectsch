Monopoly (C Project)
Simple C program that simulates a basic Monopoly board structure. It loads property data and board configuration from external files, assigns properties to board spaces, and prints the resulting board state. The project demonstrates the use of structs, enums, arrays, pointers, and file parsing in C.

Features
Loading property definitions from a text file
Loading board layout from a text file
Mapping properties to board spaces using pointers
Printing formatted board output
Basic error handling for invalid input files
Compilation
gcc main.c monopoly.c -o monopoly
Usage
./monopoly -t properties.txt -b board.txt
Input format
Properties file
[COLOR]
"PROPERTY NAME":PRICE
Board file
<number_of_spaces>
SPACE_TYPE
SPACE_TYPE
...
Error handling
E1 – file cannot be opened
E2 – invalid board configuration (not enough properties)
