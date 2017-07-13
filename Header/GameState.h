#pragma once


char changePlayer(char player); // Zmiana gracza podanego przez parametr, zwraca znak gracza nastepnego
int didTheGameEnd(Board board, char player, Position lastPosition);//Funkcja pomocnicza, używająca poprzednich czterech funkcji, do ustalenia aktualnego stanu gry.Zwraca ona 1 jeśli któryś z warunków wygranej został osiągniety, -1 jeśli żaden z graczy nie wygrał i nie ma już wolnych miejsc na planszy, 0  jeśli gra nie została ukończona.
int verticalWin(Board board, char player, Position lastPosition);
int horizontalWin(Board board, char player, Position lastPosition);
int diagonalWin(Board board, char player, Position lastPosition);
int reverseDiagonalWin(Board board, char player, Position lastPosition);
// Funkcje sprawdzające planszę będącą składową struktury Board, 
//zaczynając od pozycji podanej przez parametr lastPosition, czy gracz przekazany do funkcji poprzez parametr player wygrał. 
//Zwracają 1 jeśli gracz posiada swoje znaki na całej szerokości, wysokości lub po obu przekątnych, 0 jeśli te warunki nie zaistnieją.