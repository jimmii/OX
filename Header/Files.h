#pragma once
// Funkcja tworzaca plik z rozszerzeniem .txt, w ktorym znajduja sie informacje o aktualnym stanie gry, Board board zawiera podstawowe informacje o planszy, 
//char currentPlayer: gracz ktory bedzie wykonywal ruch po wczytaniu gry, char initialPlayer: gracz poczatkowy, char* saveName: zawiera nazwe zapisu.
void saveFile(Board board, char currentPlayer, char initialPlayer, char* saveName);
// Funkcja wczytujaca zapisany stan gry z pliku, do struktury Board* board zostaną wpisane podstawowe informacje o planszy, char* currentPlayer, 
//char* initialPlayer: informacje o graczach, char* saveName: nazwa zapisu, który ma zostać wczytany.
void readFile(Board* board, char *currentPlayer, char *initialPlayer, char* saveName);
