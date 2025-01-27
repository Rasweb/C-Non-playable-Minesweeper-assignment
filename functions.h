#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct Mine {
	int x;
	int y;
} Mine;

typedef struct Gameboard {
	int x;
	int y;
	int mineCount;
	Mine* mines;
} Gameboard;

/*
* Creates a gameboard using parameters
	* Checks if the current mine is the same as the rand val
	* Adds one to the variable mineExist
	* if Minexist is zero - the rand value becomes the new mine value
*/
Gameboard createGameBoard(int x, int y, int mineCount);

// Finds the mines
int containsMine(Gameboard* g, int x, int y);

// Finds the different mines and adds a number if near
int adjacentMines(Gameboard* g, int x, int y);

// Decides what how a cell should be printed
void printCell(Gameboard* g, int x, int y, int type);

// Template for printing the board
void printBoardTemplate(Gameboard* g, int type);

// Prints the standard board
void printGameboard(Gameboard* g);

// For dynamic size and minecount
void customBoard(int* width, int* height, int* mineCount);

// For memory allocation
void freeGamboard(Gameboard* g);

// Prints only numbers in the board
void printNumbers(Gameboard* g);

// Prints only mines on the board
void printMines(Gameboard* g);

// WORKING SAFE CHECK FOR NUMBERS, not for ENTER!
void safeInput(char prompt[], int* val);

// Modifies the printCell function to save to a file instead
void fpPrintCell(Gameboard* g, int x, int y, int type, FILE* fp);

// Writes the entire board to txt file
void saveText(Gameboard* g, int type, char filename[]);

// Asks the user if they wish to save the board to a txt file
int userSaveChoice(Gameboard* g, int type, char filename[]);

// Loads a gameboard from a txt file
void loadText(char filename[]);

#endif
