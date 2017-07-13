#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Board.h"



Board initialize(int width) {
	Board board;
	board.numberOfBlanks = width*width;
	board.numberOfOccupied = 0;
	board.boardArr = makeBoard(width);
	board.numberOfSpaces = width*width;
	board.width = width;
	fillWithDashes(board);
	return board;
}

char** makeBoard(int width) {
	char** board;
	board = malloc(width * sizeof(*board));
	for (int i = 0; i < width; i++) {
		board[i] = malloc(width * sizeof(*(board[i])));
	}
	return board;
}

void freeBoard(Board board) {

	for (int i = 0; i < board.width; i++) {
		free(board.boardArr[i]);
	}
	free(board.boardArr);
}



void fillWithDashes(Board board) {

	for (int i = 0; i < board.width; i++) {
		for (int j = 0; j < board.width; j++) {
			board.boardArr[i][j] = '-';
		}
	}
}

void showBoard(Board board) {

	printf("|");
	for (int i = -1; i < board.width; i++) {
		for (int j = -1; j < board.width; j++) {
			if ((i == -1) && (j == -1)) {
				printf("  -  |");
			}
			else
				if (i == -1) {
					printf("  %d  |", j + 1);
				}
				else
					if (j == -1) {
						if (i + 1 >= 10) {
							printf("%d |  ", i + 1);
						}
						else {
							printf("%d  |  ", i + 1);
						}
					}
					else {
						if (j + 1 >= 10) {
							printf(" %c  |  ", board.boardArr[i][j]);
						}
						else {
							printf("%c  |  ", board.boardArr[i][j]);
						}
					}
		}
		if (i != board.width - 1) {
			printf("\n|  ");
		}
	}
	printf("\n");
}

void placeMark(Board* board, char mark, Position position) {

	board->numberOfBlanks--;
	board->numberOfOccupied++;
	board->boardArr[position.y][position.x] = mark;

}

char contentsOf(Position position, char** boardArr) {

	return boardArr[position.y][position.x];

}

Position* getAvaliableMoves(Board board) {

	Position* avMove = malloc(board.numberOfBlanks * sizeof(*avMove));
	Position position;

	int k = 0;
	for (int i = 0; i < board.width; i++) {
		for (int j = 0; j < board.width; j++) {
			position.x = j;
			position.y = i;
			if (contentsOf(position, board.boardArr) == '-') {
				avMove[k].x = j;
				avMove[k].y = i;
				k++;


			}

		}
	}

	return avMove;
}
