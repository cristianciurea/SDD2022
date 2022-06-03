#include "stdio.h"

void RLECompresie(char* fIn, char* fOut)
{
	FILE* fpIn = fopen(fIn, "rb");
	FILE* fpOut = fopen(fOut, "wb");
	int currChar, prevChar;
	unsigned char count = 0;
	prevChar = -1;
	//citire pana la sfarsitul fisierului
	while ((currChar = fgetc(fpIn)) != -1)
	{
		fputc(currChar, fpOut);
		//testare secventa caractere identice
		if (currChar == prevChar)
		{
			count = 0;
			//determinare numar aparitii
			while ((currChar = fgetc(fpIn)) != -1)
			{
				if (currChar == prevChar)
				{
					count++;
					if (count == 255)
					{
						fputc(count, fpOut);
						prevChar = -1;
						break;
					}
				}
				else
				{
					fputc(count, fpOut);
					fputc(currChar, fpOut);
					prevChar = currChar;
					break;
				}
			}
		}
		else
			prevChar = currChar;
		if (currChar == -1)
		{
			fputc(count, fpOut);
			break;
		}
	}
	fclose(fpIn);
	fclose(fpOut);
}

void main()
{
	RLECompresie((char*)"in.txt", (char*)"out.txt");
}