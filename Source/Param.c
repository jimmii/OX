#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void showHelp() {

	printf("\tKolko i Krzyzyk\n");
	printf("\tby Przemyslaw Chudzia\n");
	printf("============================================\n");
	printf("Parametry:\n");
	printf("\t> '-s' rozmiar planszy (domyslna i minimalna wartoscia jest 3) \n");
	printf("\t> '-i' nazwa zapisu, z ktorego chcesz wczytac stan gry (rozszerzenie .txt jest automatycznie dodawane)\n");
	printf("Gdy stan gry jest wczytywany z pliku, parametr -s jest ignorowany (informacja o rozmiarze planszy znajduje sie w pliku)\n");
}


int getWidth(char *widthString) {

	if (widthString != NULL) {
		if (atoi(widthString) < 3 || atoi(widthString) > 99999) {
			showHelp();
			exit(EXIT_FAILURE);
		}
		else {
			return atoi(widthString);
		}
	}
	else {
		showHelp();
		exit(EXIT_FAILURE);
	}
}


char * getSaveName(char *saveName) {

	if (saveName != NULL) {
		return saveName;
	}
	else {
		showHelp();
		exit(EXIT_FAILURE);
	}
}


void paramManager(int argc, char *argv[], int *width, char **saveName) {

	int validParams = 0;
	int widthParamExists = 0;


	if (argc > 1) {
		int i;
		for (i = 0; i < argc; i++) {
			if (strcmp(argv[i], "-s") == 0) {

				*width = getWidth(argv[i + 1]);
				validParams++;
				widthParamExists = 1;
			}
			else
				if (strcmp(argv[i], "-i") == 0) {

					*saveName = getSaveName(argv[i + 1]);
					validParams++;
				}
				else
					if (strcmp(argv[i], "-h") == 0) {
						showHelp();
						exit(EXIT_SUCCESS);
					}

		}
		if ((validParams == 0) || (validParams == 1 && argc > 3) || (validParams == 2 && argc > 5)) {
			showHelp();
			exit(EXIT_FAILURE);
		}
	}


}

