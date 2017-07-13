#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Board.h"
#include "GameState.h"
#include "Ai.h"

AiMove minimax(Board *board, int depth, char player, Position lastPosition, int alpha, int beta) {

	AiMove aiMove;
	AiMove newScore;

	if (didTheGameEnd(*board, (player == 'X') ? 'O' : 'X', lastPosition) == 1) {
		aiMove.x = -1;
		aiMove.y = -1;
		aiMove.score = (depth % 2 != 0) ? depth - 10 : 10 - depth;
		return aiMove;
	}
	else if (didTheGameEnd(*board, (player == 'X') ? 'O' : 'X', lastPosition) == -1) {
		aiMove.x = -1;
		aiMove.y = -1;
		aiMove.score = 0;
		return aiMove;
	}

	if (depth % 2 != 0) {
		aiMove.x = -1;
		aiMove.y = -1;
		aiMove.score = alpha;
	}
	else {
		aiMove.x = -1;
		aiMove.y = -1;
		aiMove.score = beta;
	}

	Position* avMoves = NULL;

	if (board->numberOfBlanks != 0) {
		avMoves = getAvaliableMoves(*board);
	}

	for (int i = 0; i < board->numberOfBlanks; i++) {

		placeMark(board, player, avMoves[i]);

		newScore = minimax(board, depth + 1, changePlayer(player), avMoves[i], alpha, beta);

		board->boardArr[avMoves[i].y][avMoves[i].x] = '-';
		board->numberOfBlanks++;
		board->numberOfOccupied--;

		if (depth % 2 != 0) {
			if (newScore.score > aiMove.score) {

				aiMove.score = newScore.score;
				aiMove.x = avMoves[i].x;
				aiMove.y = avMoves[i].y;
				alpha = newScore.score;

			}
		}
		else {
			if (newScore.score < aiMove.score) {
				aiMove.score = newScore.score;
				aiMove.x = avMoves[i].x;
				aiMove.y = avMoves[i].y;
				beta = newScore.score;
			}

		}

		if (alpha >= beta) {
			break;
		}
	}
	if (avMoves != NULL) {
		free(avMoves);
	}
	return aiMove;
}

Position getBestMove(Board* board, char player) {

	Position bestMove = { 0,0 };
	AiMove newMove;

	newMove = minimax(board, 1, player, bestMove, -9999, 9999);

	bestMove.x = newMove.x;
	bestMove.y = newMove.y;

	return bestMove;

}


