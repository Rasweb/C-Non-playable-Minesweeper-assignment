#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

void startPrompt() {
	printf("Welcome to my MineSweeper App\n");
	printf("1 : Print Standard Gameboard\n");
	printf("2 : Print Numbers Only Gameboard\n");
	printf("3 : Print Mines Only Gameboard\n");
	printf("4 : Randomize board\n");
	printf("5 : Load board from file\n");
	printf("6 : Quit\n");
};

int getUserChoice() {
	int selectedChoice;
	char prompt[30] = "Choose an option (1-6): ";

	safeInput(prompt, &selectedChoice);

	return selectedChoice;
}

void main()
{
	srand(time(0));
	int width, height, mineCount;

	customBoard(&width, &height, &mineCount);
	Gameboard myBoard = createGameBoard(width, height, mineCount);

	while (1) {
		// For txt files
		char filename[11] = "board.txt";
		startPrompt();

		int choice = getUserChoice();

		switch (choice)
		{
		case 1:
			printf("\nHere comes your standard gameboard:\n");
			printGameboard(&myBoard);
			userSaveChoice(&myBoard, 1, filename);
			break;
		case 2:
			printf("\nHere comes your numbers only gameboard:\n");
			printNumbers(&myBoard);
			userSaveChoice(&myBoard, 2, filename);
			break;
		case 3:
			printf("\nHere come your mines only gameboard:\n");
			printMines(&myBoard);
			userSaveChoice(&myBoard, 3, filename);
			break;
		case 4:
			printf("\nRandomzing the board:\n");
			freeGamboard(&myBoard);
			customBoard(&width, &height, &mineCount);
			myBoard = createGameBoard(width, height, mineCount);
			break;
		case 5:
			printf("\nGameboard from the file: %s\n", filename);
			loadText(filename);
			break;
		case 6:
			printf("\nQuiting the menu, goodbye:\n");
			freeGamboard(&myBoard);
			exit(0);
		default:
			printf("Not a valid number!\n");
			break;
		}
	}

}

