#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

Gameboard createGameBoard(int xInp, int yInp, int mineCountInp) {
	int placedMines = 0;
	Gameboard board;

	board.x = xInp;
	board.y = yInp;
	board.mineCount = mineCountInp;

	board.mines = (Mine*)malloc(mineCountInp * sizeof(Mine));
	if (board.mines == NULL) {
		printf("Memory Allocation failed\n");
		exit(0);
	}

	do
	{
		int mineExist = 0;
		int x = rand() % xInp;
		int y = rand() % yInp;

		for (int i = 0; i < mineCountInp; i++) {
			if (board.mines[i].x == x && board.mines[i].y == y) {
				mineExist = 1;
				break;
			}
		}
		if (!mineExist) {
			board.mines[placedMines].x = x;
			board.mines[placedMines].y = y;
			placedMines++;
		}
	} while (placedMines < board.mineCount);

	return board;
}

int containsMine(Gameboard* g, int x, int y) {
	for (int i = 0; i < g->mineCount; i++)
	{
		if (g->mines[i].x == x && g->mines[i].y == y) {
			return 1;
		}
	}
	return 0;
}

int adjacentMines(Gameboard* g, int x, int y) {
	int count = 0;

	int aboveY = y + 1;
	int underY = y - 1;
	int rightToX = x + 1;
	int leftToX = x - 1;

	for (int i = 0; i < g->mineCount; i++)
	{
		int mineX = g->mines[i].x;
		int mineY = g->mines[i].y;

		int isAboveX = (mineY == aboveY && mineX == x);
		int isAboveRight = (mineY == aboveY && mineX == rightToX);
		int isAboveLeft = (mineY == aboveY && mineX == leftToX);
		int isUnder = (mineY == underY && mineX == x);
		int isUnderRight = (mineY == underY && mineX == rightToX);
		int isUnderLeft = (mineY == underY && mineX == leftToX);
		int isLeft = (mineY == y && mineX == leftToX);
		int isRight = (mineY == y && mineX == rightToX);

		if (isAboveX || isAboveRight || isAboveLeft || isUnder || isUnderRight || isUnderLeft || isLeft || isRight) {
			count++;
		}
	}
	return count;
}

void printCell(Gameboard* g, int x, int y, int type) {
	int minesNear = adjacentMines(g, x, y);
	int mine = containsMine(g, x, y);

	if (type == 1) {
		if (mine == 1) {
			printf("*");
		}
		else if (minesNear) {
			printf("%d", minesNear);
		}
		else {
			printf(" ");
		}
	}

	if (type == 2) {
		if (minesNear) {
			printf("%d", minesNear);
		}
		else {
			printf(" ");
		}
	}

	if (type == 3) {
		if (mine == 1) {
			printf("*");
		}
		else {
			printf(" ");
		}
	}
}

void printBoardTemplate(Gameboard* g, int type) {

	printf("+");
	for (int topLine = 0; topLine < g->x; topLine++)
	{
		printf("-");
	}
	printf("+\n");

	for (int y = 0; y < g->y; y++)
	{

		printf("|");
		for (int x = 0; x < g->x; x++) {
			printCell(g, x, y, type);
		}

		printf("|\n");
	}

	printf("+");
	for (int BottomLine = 0; BottomLine < g->x; BottomLine++)
	{
		printf("-");
	}
	printf("+\n");
}

void printGameboard(Gameboard* g) {
	printBoardTemplate(g, 1);
}

void customBoard(int* width, int* height, int* mineCount) {

	char WidthPrompt[32] = "Write the width(x: 1 - 110): ";
	char Heightprompt[32] = "Write the height(y: 1 - 500): ";
	char Mineprompt[44] = "Write the number of mines(Less then x*y): ";
	char standardPrompt[40] = "Value is not within the accepted range\n";

	safeInput(WidthPrompt, width);

	while (*width >= 111 || *width <= 0) {
		printf("%s", standardPrompt);
		safeInput(WidthPrompt, width);
	}
	safeInput(Heightprompt, height);
	while (*height >= 501 || *height <= 0) {
		printf("%s", standardPrompt);
		safeInput(Heightprompt, height);
	}
	safeInput(Mineprompt, mineCount);

	int sum = *width * *height;
	while (sum < *mineCount || *mineCount <= 0) {
		printf("%s", standardPrompt);
		safeInput(Mineprompt, mineCount);
	}
}

void freeGamboard(Gameboard* g) {
	if (g->mines != NULL) {
		free(g->mines);
		g->mines = NULL;
	}
}

void printNumbers(Gameboard* g) {
	printBoardTemplate(g, 2);
}

void printMines(Gameboard* g) {
	printBoardTemplate(g, 3);
}

void safeInput(char prompt[], int* val) {
	printf("%s", prompt);
	do {
		int res = scanf_s("%d", val);

		if (res != 1) {
			while (getchar() != '\n');
			printf("%s", prompt);
		}
		else {
			break;
		}
	} while (*val < 1 || *val > 6);
}

void fpPrintCell(Gameboard* g, int x, int y, int type, FILE* fp) {
	int minesNear = adjacentMines(g, x, y);
	int mine = containsMine(g, x, y);

	if (type == 1) {
		if (mine == 1) {
			fprintf(fp, "*");
		}
		else if (minesNear) {
			fprintf(fp, "%d", minesNear);
		}
		else {
			fprintf(fp, " ");
		}
	}

	if (type == 2) {
		if (minesNear) {
			fprintf(fp, "%d", minesNear);
		}
		else {
			fprintf(fp, " ");
		}
	}

	if (type == 3) {
		if (mine == 1) {
			fprintf(fp, "*");
		}
		else {
			fprintf(fp, " ");
		}
	}
}

void saveText(Gameboard* g, int type, char filename[]) {
	FILE* fp;

	fopen_s(&fp, filename, "w");

	if (fp == NULL) {
		printf("Could not find/open the file: %s\n", filename);
		return;
	}


	fprintf(fp, "+");
	for (int topLine = 0; topLine < g->x; topLine++)
	{
		fprintf(fp, "-");
	}
	fprintf(fp, "+\n");

	for (int y = 0; y < g->y; y++)
	{

		fprintf(fp, "|");
		for (int x = 0; x < g->x; x++) {
			fpPrintCell(g, x, y, type, fp);
		}

		fprintf(fp, "|\n");
	}


	fprintf(fp, "+");
	for (int BottomLine = 0; BottomLine < g->x; BottomLine++)
	{
		fprintf(fp, "-");
	}
	fprintf(fp, "+\n");

	fclose(fp);
}

int userSaveChoice(Gameboard* g, int type, char filename[]) {
	char choice;
	printf("Do you wish to save your result to a text file(y/n)? ");
	scanf_s(" %c", &choice);
	int toInt = (int)choice;

	if (choice == 121) {
		saveText(g, type, filename);
		printf("Text successfully saved\n");
		printf("\n");
		return 1;
	}
	else {
		printf("Text has not been saved\n");
		printf("\n");
		return 0;
	}
}

void loadText(char filename[]) {
	FILE* fp;
	int ch;
	fopen_s(&fp, filename, "r");
	if (fp == NULL) {
		printf("Could not find/open the file %s", filename);
		return;
	}

	while ((ch = fgetc(fp)) != EOF) {
		printf("%c", ch);
	}
	printf("\n");

	fclose(fp);
}