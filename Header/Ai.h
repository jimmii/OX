#pragma once


typedef struct AiMove {
	int x;
	int y;
	int score;
}AiMove;

Position getBestMove(Board* board, char player);// Funkcja pomocnicza korzystająca z funkcji minimax.W parametrze player znajduje się znak, którym gra komputer, a w parametrze board, podstawowe informacje o planszy w danej chwili.Zwraca strukture Position, w której znajdują się współrzędne z najlepszym możliwym ruchem.
AiMove minimax(Board *board, int depth, char player, Position lastPosition, int alpha, int beta);//Funkcja rekurencyjna realizująca algorytm minimax z odcięciem alfa beta. Przez parametr int depth do funkcji jest przekazany poziom na którym aktualnie znajduje się funkcja. Zwraca ona strukture AiMove, w której znajduje się najlepszy możliwy ruch, który kompter może wykonac wraz z jego punktacją.