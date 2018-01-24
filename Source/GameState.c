#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Board.h"

char changePlayer(char player) {//testowy komentarz

	return (player == 'X') ? 'O' : 'X';
}


int didTheGameEnd(Board board, char player, Position lastPosition) {

	if (verticalWin(board, player, lastPosition) ||
		horizontalWin(board, player, lastPosition) ||
		diagonalWin(board, player, lastPosition) ||
		reverseDiagonalWin(board, player, lastPosition)) {
		
		return 1;
	}
	else if (board.numberOfOccupied == board.numberOfSpaces) {
		
		return -1;
	}
	else {
		return 0;
	}


}


int verticalWin(Board board, char player, Position lastPosition) {
	for (int i = 0; i < board.width; i++) {
		if (board.boardArr[i][lastPosition.x] != player) {
			return 0;
			break;
		}
		if (i == board.width - 1) {
			
			return 1;
			
		}
	}

}


int horizontalWin(Board board, char player, Position lastPosition) {

	for (int i = 0; i < board.width; i++) {

		if (board.boardArr[lastPosition.y][i] != player) {  
			return 0;								 
			break;
		}
		if (i == board.width - 1) {
			return 1;
		}
	}

}


int diagonalWin(Board board, char player, Position lastPosition) {

	if ((lastPosition.x) == (lastPosition.y)) {

		for (int i = 0; i < board.width; i++) {
			if (board.boardArr[i][i] != player) {
				return 0;
				break;
			}
			if (i == board.width - 1) {
				return 1;
			}
		}
	}


	
	return 0;
}

int reverseDiagonalWin(Board board, char player, Position lastPosition) {
	if ((lastPosition.x) + (lastPosition.y) == board.width - 1) {
		for (int i = 0; i < board.width; i++) {
			if (board.boardArr[i][(board.width - 1) - i] != player) {
				return 0;
				break;
			}
			if (i == board.width - 1) {
				return 1;
			}
		}
	}
	return 0;
}
