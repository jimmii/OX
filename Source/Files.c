#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Board.h"




void saveFile(Board board, char currentPlayer, char initialPlayer, char* saveName) {

	errno_t err;
	FILE* f = NULL;
	char path[70];
	struct stat s = { 0 };

	if (stat("saves", &s) != 0) {
		mkdir("saves");
	}

	snprintf(path, 70, "%s%s%s", "saves/", saveName, ".txt");
	err = fopen_s(&f, path, "w");
	if (err != 0) {
		printf("Nie mozna bylo otworzyc pliku: %s\n", saveName);
	}
	else {
		fprintf_s(f, "%d;%c;%c", board.width, currentPlayer, initialPlayer);
		fprintf_s(f, "\n");
		for (int i = 0; i < board.width; i++) {
			for (int j = 0; j < board.width; j++) {
				fprintf_s(f, "%c", board.boardArr[i][j]);
			}
			fprintf_s(f, ";");
		}
	}
	if (f)
	{
		fclose(f);
	}
	free(saveName);
}

void readFile(Board* board, char *currentPlayer, char *initialPlayer, char* saveName) {
	char ch;
	int x = 0;
	int y = 0;
	int width = 0;
	Position position;
	errno_t err;
	FILE* f = NULL;
	char path[70];

	snprintf(path, 70, "%s%s%s", "saves/", saveName, ".txt");
	err = fopen_s(&f, path, "r");
	if (err != 0) {
		printf("Blad w ladowaniu zapisu stanu gry o nazwie: %s\n", saveName);
		exit(EXIT_FAILURE);
	}
	else {
		for (int i = 0; i < 5;i++) {
			ch = (char)fgetc(f);
			switch (i) {
			case 0:
				width = ch - '0';
				if (width < 3) {
					printf("Wielkosc planszy musi byc >= 3");
					exit(EXIT_FAILURE);
				}
				else if ((ch < '0') || (ch > '9')) {
					printf("Wielkosc planszy musi byc liczba");
					exit(EXIT_FAILURE);
				}
				break;
			case 2:
				if ((ch != 'X') && (ch != 'O')) {
					printf("Blad w strukturze pliku");
					exit(EXIT_FAILURE);
				}
				else {
					*currentPlayer = ch;
				}
				break;
			case 4:
				if (((ch != 'X') && (ch != 'O'))) {
					printf("Blad w strukturze pliku");
					exit(EXIT_FAILURE);
				}
				else {
					*initialPlayer = ch;
				}
				break;
			}
		}
		*board = initialize(width);     
		(char)fgetc(f);
		for (int i = 0; i < width*width + width;i++) {
			position.x = x;
			position.y = y;
			ch = (char)fgetc(f);
			if (ch != ';') {
				if ((ch != 'X') && (ch != 'O') && (ch != '-')) {
					printf("Blad w strukturze pliku");
					exit(EXIT_FAILURE);
				}
				if (ch != '-') {
					placeMark(board, ch, position);
				}
				x++;
			}
			else {
				y++;
				x = 0;
			}
			if (x > width) {
				printf("Blad w strukturze pliku");
				exit(EXIT_FAILURE);
			}
		}
	}
	if (f)
	{
		fclose(f);
	}
}





