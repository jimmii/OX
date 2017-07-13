#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Param.h"
#include "Board.h"
#include "GameState.h"
#include "Ai.h"
#include "Files.h"

//Funkcja wykonująca turę każdego z graczy, wyświetla planszę oraz sprawdza stan gry. Jeśli gra się zakończy, usuwa przydzieloną pamięc tablicy z planszą i wyświetla odpowiedni komunikat. Zwraca  1 jeśli któryś z graczy wygrał, -1 jeśli jest remis i 0 jeśli gra może się toczyć dalej.
int turn(Board* board, char* currentPlayer, Position position);
//Pyta użytkownika o współrzędne na których chce użytkownik chce umieścić swój znak. Zwraca strukturę typu Position z tymi współrzędnymi.
Position askForCoords(Board board);
//Funkcja sprawdzająca czy współrzędne podane w poprzedniej funkcji są prawidłowe, jeśli nie wyświetla odpowiedni komunikat i zwraca 0, w przeciwnym wypadku zwraca 1.
int isPositionValid(Board board, Position position);
//Funkcja pytająca użytkownika o to jakim znakiem chce grać, w przypadku podania błędnych danych prosi jeszcze raz o ich podanie.Zwraca ten znak.
char markChoice();
//Funkcja prosi o podanie nazwy zapisu. Zwraca tą nazwę.
char* askForSaveName();
//Funkcja ta sprawdza czy zapis o podanej nazwie istnieje lub czy jest poprawny, jeśli jest poprawny i nie istnieje zwraca 1, w przeciwnym wypadku 0.
int isSaveNameValid(char* saveName);
//Funkcja pytająca o chęć zapisania stanu gry.W przypadku pozytywnej odpowiedzi, zapisuje go.
void saveAGame(Board board, char currentPlayer, char initialPlayer);

int main(int argc, char *argv[]) {

	int width = 3;
	char* fileName = NULL;
	Board board = { NULL, 0, 0, 0, 0 };
	paramManager(argc, argv, &width, &fileName);
	char initialPlayer;
	char currentPlayer;

	if (fileName != NULL) {
		readFile(&board, &currentPlayer, &initialPlayer, fileName);
	}
	else {
		board = initialize(width);
		initialPlayer = markChoice();
		currentPlayer = initialPlayer;
	}

	int endFlag = 0;

	Position position = { 0,0 };
	int count = 0;
	showBoard(board);
	while (endFlag != 1 && endFlag != -1) {
		count++;
		if (currentPlayer == initialPlayer) {
			printf("Gracz wykonuje swoj ruch ( %c ): \n", currentPlayer);
			position = askForCoords(board);
		}
		else {
			printf("Komputer wykonuje swoj ruch ( %c ): \n", currentPlayer);
			position = getBestMove(&board, currentPlayer);
		}
		endFlag = turn(&board, &currentPlayer, position);
		if (board.boardArr != NULL && count % 2 == 0) {
			saveAGame(board, currentPlayer, initialPlayer);
		}
	}
	return 0;
}

int turn(Board* board, char* currentPlayer, Position position) {

	placeMark(board, *currentPlayer, position);
	showBoard(*board);
	int terminalState = didTheGameEnd(*board, *currentPlayer, position);

	switch (terminalState) {
	case -1:
		printf("Remis");
		freeBoard(*board);
		board->boardArr = NULL;
		break;
	case 0:
		*currentPlayer = changePlayer(*currentPlayer);
		break;
	case 1:
		printf("%c wygral", *currentPlayer);
		freeBoard(*board);
		board->boardArr = NULL;
	}
	return terminalState;
}


Position askForCoords(Board board) {

	Position position = { 0, 0 };
	char ch;
	int x, y;

	do {
		printf("Gdzie chcesz wykonac ruch?\n");
		printf("x: \n");
		scanf_s("%d", &x);
		printf("y: \n");
		scanf_s("%d", &y);
		position.x = x - 1;
		position.y = y - 1;
		while ((ch = getchar()) != '\n');
	} while (!isPositionValid(board, position));
	return position;
}

int isPositionValid(Board board, Position position) {

	if (position.x >= board.width || position.y >= board.width || position.x < 0 || position.y < 0) {
		printf("Wprowadziles zle dane, wspolrzedne powinny byc z przedzialu: >= 1 & <= %d \n", board.width);
		return 0;
	}
	else if (contentsOf(position, board.boardArr) != '-') {
		printf("To miejsce jest juz zajete\n");
		return 0;
	}
	else {
		return 1;
	}
}

char *askForSaveName() {
	char ch;
	char* saveName = malloc(45 * sizeof(*saveName));

	do {
		printf("Podaj nazwe: \n");
		scanf_s("%44s", saveName, 45);
		while ((ch = getchar()) != '\n');
	} while (!isSaveNameValid(saveName));

	return saveName;
}




int isSaveNameValid(char* saveName) {

	struct stat s = { 0 };
	char path[70];
	char* invalidCh = "/\:*?„<>|";
	snprintf(path, 70, "%s%s%s", "saves/", saveName, ".txt");

	if (stat(path, &s) == 0) {
		printf("Zapis o podanej nazwie juz istnieje!\n");
		return 0;

	}
	else if (strpbrk(saveName, invalidCh) != NULL) {
		printf("Niedozwolone znaki w nazwie\n");
		return 0;
	}

	else {
		return 1;
	}
}

void saveAGame(Board board, char currentPlayer, char initialPlayer) {

	char ch;
	int answer;

	printf("Zapisac stan gry?\n");
	do {
		printf("1 - Tak 2 - Nie\n");
		scanf_s("%d", &answer);
		while ((ch = getchar()) != '\n');
	} while (answer != 1 && answer != 2);

	if (answer == 1) {
		saveFile(board, currentPlayer, initialPlayer, askForSaveName());
	}
}

char markChoice() {

	char ch;
	int mark;

	do {
		printf("Wybierz znak, ktorym chcesz zagrac:\n1 - X 2 - O\n");
		scanf_s("%d", &mark);
		while ((ch = getchar()) != '\n');
	} while (mark != 1 && mark != 2);
	return (mark == 1) ? 'X' : 'O';
}


