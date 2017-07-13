#pragma once


void showHelp(); //Funkcja wyświetlająca pomoc.
void paramManager(int argc, char *argv[], int *boardSize, char **saveName);//Funkcja wyszukująca spośród parametrów programu, przekazanych do funkcji przez parametr char *argv[], parametrów -s, -i, -h. 
char * getSaveName(char *saveName);//Funkcja pomocnicza sprawdzająca czy nazwa zapisu podana przez parametr saveName istnieje. Zwraca nazwę zapisu, lub kod błędu.
int getWidth(char *widthString); //Funkcja pomocnicza zamieniająca ciąg znaków podany przez parametr char *widthString, na typ int.W przypadku wystąpienia błędów, wyświetla pomoc oraz zwraca kod błędu, w przeciwnym wypadku zwraca wartość typu int.

