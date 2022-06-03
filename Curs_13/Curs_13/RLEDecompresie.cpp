#include <stdio.h>
#include <string.h>

void RLEEncode(char* inFile, char* outFile) {
	FILE* f, * g;

	//deschidere fisiere in clar, respectiv codificat
	if ((f = fopen(inFile, "rb")) == NULL)
		return;

	if ((g = fopen(outFile, "wb")) == NULL) {
		fclose(f);
		return;
	}

	int currChar, prevChar;
	unsigned int count;

	prevChar = -1;
	count = 0;

	while ((currChar = fgetc(f)) != -1) {
		//scrierea in fisierul codat RLE a simbolului
		fputc(currChar, g);

		if (currChar == prevChar) {
			count = 0;

			while ((currChar = fgetc(f)) != -1) {
				if (currChar == prevChar) {
					count++;

					if (count == 255) {
						//scriere in fisier codat RLE a frecventei de aparitie
						fputc(count, g);

						//forteaza ca simbolului urmator sa fie diferit de simbolul curent
						prevChar = -1;
						break;
					}
				}
				else {
					fputc(count, g);
					fputc(currChar, g);
					prevChar = currChar;
					break;
				}
			}
		}
		else
			prevChar = currChar;
	}

	if (currChar == -1) {
		//s-a atins EOF
		fputc(count, g);
	}

	fclose(f);
	fclose(g);
}

void RLEDecode(char* inFile, char* outFile) {
	FILE* f, * g;

	//deschidere fisiere in clar, respectiv codificat
	if ((f = fopen(inFile, "rb")) == NULL)
		return;

	if ((g = fopen(outFile, "wb")) == NULL) {
		fclose(f);
		return;
	}

	int currChar, prevChar;
	unsigned int count;

	prevChar = -1;

	while ((currChar = fgetc(f)) != -1) {
		//scriere simbol curent in fisierul decodificat
		fputc(currChar, g);

		if (currChar == prevChar) {
			count = fgetc(f);
			while (count) {
				fputc(currChar, g);
				count--;
			}

			prevChar = -1;
		}
		else
			prevChar = currChar;
	}

	fclose(f);
	fclose(g);
}

void main()
{
	RLEEncode((char*)"in.txt", (char*)"out.txt");
	RLEDecode((char*)"out.txt", (char*)"new_in.txt");
}