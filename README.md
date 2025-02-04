## Table of contents
- [Overview](#overview)
  - [Minesweeper Gameboard](#minesweeper-gameboard)
  - [Built With](#built-with)
  - [In Action](#in-action)

## Overview
### Minesweeper Gameboard
A C assignment connected to my system developer education.
The main cpp file is "Inlämning 2.cpp".
The assignment took its inspiration from this: "https://minesweeper.online/".

This assignment creates a minesweeper gameboard:
* It asks the user for width, height and the number of mines in the gameboard.
* Then it gives the user different choices to print out that gameboard.
* It can also save to a text file and load from one.

### Built With

- C
- srand() - Randomizer library
- header and body files
- Structs

### In Action

```
Write the width(x: 1 - 110): 10
Write the height(y: 1 - 500): 10
Write the number of mines(Less then x*y): 20
Welcome to my MineSweeper App
1 : Print Standard Gameboard
2 : Print Numbers Only Gameboard
3 : Print Mines Only Gameboard
4 : Randomize board
5 : Load board from file
6 : Quit
Choose an option (1-6): 1

Here comes your standard gameboard:
+----------+
|1222*1    |
|1**211  11|
|123221112*|
|  1*3*33*2|
|  12*3**32|
|121212222*|
|*3*2121111|
|*423*2*211|
|*21*2223*1|
|11111 1*21|
+----------+
Do you wish to save your result to a text file(y/n)? y
Text successfully saved

Welcome to my MineSweeper App
1 : Print Standard Gameboard
2 : Print Numbers Only Gameboard
3 : Print Mines Only Gameboard
4 : Randomize board
5 : Load board from file
6 : Quit
Choose an option (1-6):
```
