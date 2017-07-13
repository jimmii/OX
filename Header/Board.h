#pragma once


typedef struct Position {

	int x;
	int y;

}Position;

typedef struct Board {

	char ** boardArr;
	int numberOfOccupied;
	int numberOfBlanks;
	int width;
	int numberOfSpaces;

}Board;


Board initialize(int width); // Funkcja ta inicjalizuje składowe struktury typu Board. W parametrze width znajduje się szerokość planszy.
char** makeBoard(int width); // Funkcja alokująca pamięć dla dwuwymiarowej tablicy typu char o rozmiarze podanym przez parametr width i ją zwracająca.
void freeBoard(Board board); // Funkcja ta usuwa zaalokowaną pamięć dla dwuwymiarowej tablicy typu char, będącą składową struktury typu Board.
void fillWithDashes(Board board); // Funkcja wypełniająca każde pole tablicy znakiem „-”. 
void showBoard(Board board); // Funkcja wyświetla planszę gry.
void placeMark(Board* board, char mark, Position position); // Umieszcza znak podany przez parametr mark, na pozycji przesłanej do funkcji przez parametr position, zmniejsza ilość wolnych miejsc i zwiększa ilość zajętych – pola te są składowymi struktury typu Board.
char contentsOf(Position position, char** boardArr); // Zwraca znak będący na miejscu podanym przez parametr position.
Position* getAvaliableMoves(Board board); // Funkcja tworząca tablicę z dostępnymi ruchami, korzysta ze składowych struktury typu Board. Zwraca tą tablicę.
